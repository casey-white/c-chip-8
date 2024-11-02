#ifndef VIDEO_H
#define VIDEO_H

typedef struct {

} VideoConfig;

int init_video(void);
int render_frame(void);
int cleanup(void);

#endif