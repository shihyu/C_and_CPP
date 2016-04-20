#ifndef _CDPLAYER_H_
#define _CDPLAYER_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    EV_STOP,
    EV_PLAY_PAUSE
} EventCode;

void initialize();
void onEvent(EventCode ec);
void stopPlayer();
void pausePlayer();
void resumePlayer();
void startPlayer();

// for test
extern int cmdIdx;
extern const char *buf[10];

#ifdef __cplusplus
}
#endif

#endif
