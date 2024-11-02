#ifndef VIDEO_H
#define VIDEO_H

typedef struct {

} VideoConfig;

int init_video(void);
int render_frame(u_int8_t *video_buffer);
int cleanup_video(void);

#endif