#include <stdbool.h>
#include "cdplayer.h"

bool playflag;
bool pauseflag;

int cmdIdx = 0;
const char *buf[10];

void initialize() {
    cmdIdx = 0;
    playflag = false;
    pauseflag = false;
}

void onEvent(EventCode ec) {
    switch (ec) {
    case EV_STOP:
        if (playflag == true || pauseflag == true)
            stopPlayer();
        break;

    case EV_PLAY_PAUSE:
        if (playflag == true) pausePlayer();
        else if (pauseflag == true) resumePlayer();
        else startPlayer();
        break;

    default:
        break;
    }
}

void stopPlayer() {
    pauseflag = false;
    playflag = false;
    buf[cmdIdx++] = "stop";
}

void pausePlayer() {
    pauseflag = true;
    playflag = false;
    buf[cmdIdx++] = "pause";
}

void resumePlayer() {
    pauseflag = false;
    playflag = true;
    buf[cmdIdx++] = "resume";
}

void startPlayer() {
    pauseflag = false;
    playflag = true;
    buf[cmdIdx++] = "start";
}
