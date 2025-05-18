#include "unity.h"
#include "cpu.h"

void setUp(void) {
    // Empty setup function; runs before each test
}

void tearDown(void) {
    // Empty teardown function; runs after each test
}

void test_create_next_action() {
    PCAction pca = create_next_action();
    TEST_ASSERT_EQUAL(pca.action_type, ACTION_NEXT);
}

void test_create_skip_action() {
    PCAction pca = create_skip_action();
    TEST_ASSERT_EQUAL(pca.action_type, ACTION_SKIP);
}

void test_create_step_back_action() {
    PCAction pca = create_step_back_action();
    TEST_ASSERT_EQUAL(pca.action_type, ACTION_STEP_BACK);
}

void test_create_jump_action() {
    PCAction pca = create_jump_action(2);
    TEST_ASSERT_EQUAL(pca.action_type, ACTION_JUMP);
    TEST_ASSERT_EQUAL(pca.jump_address, 2);
}

void test_init_cpu() {
    CPU cpu = init_cpu();
    TEST_ASSERT_EQUAL(cpu.program_counter, 0x200);
    TEST_ASSERT_EQUAL(cpu.delay_timer, 0);
    TEST_ASSERT_EQUAL(cpu.sound_timer, 0);
    TEST_ASSERT_EQUAL(cpu.stack_pointer, 0);
    TEST_ASSERT_EQUAL(cpu.index_register, 0);
    TEST_ASSERT_EQUAL(cpu.general_registers[0], 0);
    TEST_ASSERT_EQUAL(cpu.stack[0], 0);
}

void test_clear() {
    Memory mem = init_memory();
    memset(&mem.video_buffer, 1, sizeof(bool) * (32 * 64));
    TEST_ASSERT_EQUAL(mem.video_buffer[0], 1);
    clear(&mem);
    TEST_ASSERT_EQUAL(mem.video_buffer[0], 0);
}

void test_ret() {
    CPU cpu = init_cpu();
    cpu.stack_pointer = 1;
    cpu.stack[1] = 0x95;
    PCAction pca = ret(&cpu);
    TEST_ASSERT_EQUAL(pca.jump_address, 0x95);
    TEST_ASSERT_EQUAL(cpu.stack_pointer, 0);
}

void test_jump() {
    CPU cpu = init_cpu();
    PCAction pca = jump(0x25);
    TEST_ASSERT_EQUAL(pca.jump_address, 0x25);
}

void test_call() {
    CPU cpu = init_cpu();
    PCAction pca = call(&cpu, 0x25);
    TEST_ASSERT_EQUAL(cpu.stack_pointer, 1);
    TEST_ASSERT_EQUAL(cpu.stack[0], 0x25);
}

void test_skip_equal() {
    CPU cpu = init_cpu();
    unsigned short target_register = 0x1;
    unsigned short value = 0x25;
    cpu.general_registers[target_register] = value;
    PCAction pca = skip_equal(&cpu, target_register, value);
    TEST_ASSERT_EQUAL(pca.action_type, ACTION_SKIP);
}

void test_skip_if_registers_equal() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x0] = 2;
    cpu.general_registers[0x1] = 2;
    PCAction pca = skip_if_registers_equal(&cpu, 0x0, 0x1);
    TEST_ASSERT_EQUAL(pca.action_type, ACTION_SKIP);
}

void test_load_registers() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x0] = 0x2;
    PCAction pca = load_register(&cpu, 0x0, 0x90);
    TEST_ASSERT_EQUAL(pca.action_type, ACTION_NEXT);
    TEST_ASSERT_EQUAL(cpu.general_registers[0x0], 0x90);
}

void test_add_register() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x0] = 0x1;
    PCAction pca = add_register(&cpu, 0x0, 0x3);
    TEST_ASSERT_EQUAL(cpu.general_registers[0x0], 0x4);
}

void test_load_register_to_register() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x0] = 0x0;
    cpu.general_registers[0x1] = 0x5;
    PCAction pca = load_register_to_register(&cpu, 0x0, 0x1);
    TEST_ASSERT_EQUAL(cpu.general_registers[0x0], 0x5);
}

void test_or() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x0] = 0b0101;
    cpu.general_registers[0x1] = 0b1010;
    PCAction pca = or(&cpu, 0x0, 0x1);
    TEST_ASSERT_EQUAL(cpu.general_registers[0x0], 0b1111);
}

void test_and() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x0] = 0b1111;
    cpu.general_registers[0x1] = 0b1010;
    PCAction pca = and(&cpu, 0x0, 0x1);
    TEST_ASSERT_EQUAL(cpu.general_registers[0x0], 0b1010);
}

void test_xor() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x0] = 0b1001;
    cpu.general_registers[0x1] = 0b1100;
    PCAction pca = xor(&cpu, 0x0, 0x1);
    TEST_ASSERT_EQUAL(cpu.general_registers[0x0], 0b0101);
}

void test_add_with_carry() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x0] = 0xF0;
    cpu.general_registers[0x1] = 0xF0;
    PCAction pca = add_with_carry(&cpu, 0x0, 0x1);
    TEST_ASSERT_EQUAL(cpu.general_registers[0xF], 1);
    TEST_ASSERT_EQUAL(cpu.general_registers[0x0], 224);
}

void test_subtract_with_borrow() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x0] = 0x0F;
    cpu.general_registers[0x1] = 0xF0;
    PCAction pca = subtract_with_borrow(&cpu, 0x0, 0x1);
    TEST_ASSERT_EQUAL(cpu.general_registers[0xF], 1);
    TEST_ASSERT_EQUAL(cpu.general_registers[0x0], 225);
}

void test_shift_right() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x0] = 0xFF;
    PCAction pca = shift_right(&cpu, 0x0);
    TEST_ASSERT_EQUAL(cpu.general_registers[0x0], 0x7F);
    TEST_ASSERT_EQUAL(cpu.general_registers[0xF], 1);
}

void test_shift_left() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x0] = 0xFF;
    PCAction pca = shift_left(&cpu, 0x0);
    TEST_ASSERT_EQUAL(cpu.general_registers[0x0], 0xFE);
    TEST_ASSERT_EQUAL(cpu.general_registers[0xF], 1);
}

void test_skip_if_registers_not_equal() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x0] = 0xFF;
    PCAction pca = skip_if_registers_not_equal(&cpu, 0x0, 0x1);
    TEST_ASSERT_EQUAL(pca.action_type, ACTION_SKIP);
}

void test_load_index() {
    CPU cpu = init_cpu();
    PCAction pca = load_index(&cpu, 0xFFF);
    TEST_ASSERT_EQUAL(cpu.index_register, 0xFFF);
}

void test_jump_to() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x0] = 0xF;
    PCAction pca = jump_to(&cpu, 0xFF0);
    TEST_ASSERT_EQUAL(pca.action_type, ACTION_JUMP);
    TEST_ASSERT_EQUAL(pca.jump_address, 0xFFF);
}

void test_random_byte() {
    CPU cpu = init_cpu();
    random_byte(&cpu, 0, 0x93);
    TEST_ASSERT_NOT_EQUAL(0, cpu.general_registers[0x0]);
}

void test_skip_if_key_press() {
    CPU cpu = init_cpu();
    cpu.keypad[0x3] = true;
    cpu.keypad[0x1] = false;
    cpu.general_registers[0x0] = 0x3;
    cpu.general_registers[0x1] = 0x1;
    PCAction pca_success = skip_if_key_press(&cpu, 0x0);
    TEST_ASSERT(pca_success.action_type == ACTION_SKIP);
    PCAction pca_failure = skip_if_key_press(&cpu, 0x1);
    TEST_ASSERT(pca_failure.action_type == ACTION_NEXT);
}

void test_load_delay_timer() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x3] = 108;
    load_delay_timer(&cpu, 0x3);
    TEST_ASSERT_EQUAL(108, cpu.delay_timer);
}

void test_load_sound_timer() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x3] = 108;
    load_sound_timer(&cpu, 0x3);
    TEST_ASSERT_EQUAL(108, cpu.sound_timer);
}

void test_load_sprite() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x0] = 3;
    load_sprite(&cpu, 0);
    unsigned char expected = 0x50 + 15;
    TEST_ASSERT_EQUAL(expected, cpu.index_register);
}

void test_load_bcd() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x2] = 117;
    cpu.index_register = 2;
    load_bcd(&cpu, 0x2);
    unsigned char hundred = read_at(&cpu.memory, 2);
    unsigned char ten = read_at(&cpu.memory, 3);
    unsigned char one = read_at(&cpu.memory, 4);
    TEST_ASSERT_EQUAL(hundred, 1);
    TEST_ASSERT_EQUAL(ten, 1);
    TEST_ASSERT_EQUAL(one, 7);
}

void test_add_to_index() {
    CPU cpu = init_cpu();
    cpu.general_registers[0x2] = 15;
    cpu.index_register = 0x50;
    add_to_index(&cpu, 0x2);
    TEST_ASSERT_EQUAL(0x50 + 15, cpu.index_register);
}

void test_display() {
    CPU cpu = init_cpu();
    cpu.index_register = 0x20;
    cpu.memory.memory[0x20] = 0xF0;
    cpu.general_registers[0x1] = 0;
    cpu.general_registers[0x2] = 0;

    display(&cpu, 0x1, 0x2, 1);

    TEST_ASSERT_EQUAL(cpu.memory.video_buffer[0], 1);
    TEST_ASSERT_EQUAL(cpu.memory.video_buffer[1], 1);
    TEST_ASSERT_EQUAL(cpu.memory.video_buffer[2], 1);
    TEST_ASSERT_EQUAL(cpu.memory.video_buffer[3], 1);
    TEST_ASSERT_EQUAL(cpu.memory.video_buffer[4], 0);
    TEST_ASSERT_EQUAL(cpu.memory.video_buffer[5], 0);



}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_create_next_action);
    RUN_TEST(test_create_skip_action);
    RUN_TEST(test_create_step_back_action);
    RUN_TEST(test_create_jump_action);
    RUN_TEST(test_init_cpu);
    RUN_TEST(test_clear);
    RUN_TEST(test_ret);
    RUN_TEST(test_jump);
    RUN_TEST(test_call);
    RUN_TEST(test_skip_equal);
    RUN_TEST(test_skip_if_registers_equal);
    RUN_TEST(test_load_registers);
    RUN_TEST(test_add_register);
    RUN_TEST(test_load_register_to_register);
    RUN_TEST(test_or);
    RUN_TEST(test_and);
    RUN_TEST(test_xor);
    RUN_TEST(test_add_with_carry);
    RUN_TEST(test_subtract_with_borrow);
    RUN_TEST(test_shift_right);
    RUN_TEST(test_shift_left);
    RUN_TEST(test_skip_if_registers_not_equal);
    RUN_TEST(test_load_index);
    RUN_TEST(test_jump_to);
    RUN_TEST(test_random_byte);
    RUN_TEST(test_skip_if_key_press);
    RUN_TEST(test_load_sprite);
    RUN_TEST(test_load_bcd);
    RUN_TEST(test_add_to_index);
    RUN_TEST(test_display);

    return UNITY_END();
}

