#ifndef _CDPLAYER_H_
#define _CDPLAYER_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _State {
    const struct _State *(*stop)(const struct _State *pThis);
    const struct _State *(*playOrPause)(const struct _State *This);
} State;

void initialize();
void onStop();
void onPlayOrPause();

// for test
extern int cmdIdx;
extern const char *buf[10];

#ifdef __cplusplus
}
#endif

#endif
