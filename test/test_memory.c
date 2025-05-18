#include "unity.h"
#include "memory.h"

void setUp(void) {
    // Empty setup function; runs before each test
}

void tearDown(void) {
    // Empty teardown function; runs after each test
}

void test_init_memory() {
   Memory mem = init_memory();
   TEST_ASSERT_EQUAL(0, mem.memory[0]);
   TEST_ASSERT_EQUAL(0, mem.memory[4095]); 
}

void test_read_at() {
    Memory mem = init_memory();
    mem.memory[0x200] = 0b11;
    TEST_ASSERT_EQUAL(0b11, read_at(&mem, 0x200));

    TEST_ASSERT_EQUAL(-1, read_at(&mem, -1));
}

void test_write_at() {
    Memory mem = init_memory();
    write_at(&mem, 0x200, 0b11);
    TEST_ASSERT_EQUAL(0b11, read_at(&mem, 0x200));

    TEST_ASSERT_EQUAL(-1, write_at(&mem, -1, 0b10));
}

void test_clear_memory() {
    Memory mem = init_memory();
    write_at(&mem, 0x200, 0b11);
    clear_memory(&mem);
    TEST_ASSERT_EQUAL(0, read_at(&mem, 0x200));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_init_memory);
    RUN_TEST(test_read_at);
    RUN_TEST(test_write_at);
    RUN_TEST(test_clear_memory);
    return UNITY_END();
}

