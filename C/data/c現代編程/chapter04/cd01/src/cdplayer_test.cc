#include "gtest/gtest.h"

#include <stdbool.h>
#include <string.h>
#include "cdplayer.h"

TEST(PlayTest, playOnIdleWillStartPlaying) {
    initialize();
    onEvent(EV_PLAY_PAUSE);
    EXPECT_EQ(1, cmdIdx);
    ASSERT_TRUE(strcmp(buf[0], "start") == 0);

    onEvent(EV_PLAY_PAUSE);
    EXPECT_EQ(2, cmdIdx);
    ASSERT_TRUE(strcmp(buf[1], "pause") == 0);

    onEvent(EV_PLAY_PAUSE);
    EXPECT_EQ(3, cmdIdx);
    ASSERT_TRUE(strcmp(buf[2], "resume") == 0);
}

TEST(StopTest, playOnIdleAndStopWillStopPlaying) {
    initialize();
    onEvent(EV_PLAY_PAUSE);
    EXPECT_EQ(1, cmdIdx);
    ASSERT_TRUE(strcmp(buf[0], "start") == 0);

    onEvent(EV_STOP);
    EXPECT_EQ(2, cmdIdx);
    ASSERT_TRUE(strcmp(buf[1], "stop") == 0);
}

TEST(StopTest, playOnIdleAndPauseAndStopWillStopPlaying) {
    initialize();
    onEvent(EV_PLAY_PAUSE);
    EXPECT_EQ(1, cmdIdx);
    ASSERT_TRUE(strcmp(buf[0], "start") == 0);

    onEvent(EV_PLAY_PAUSE);
    EXPECT_EQ(2, cmdIdx);
    ASSERT_TRUE(strcmp(buf[1], "pause") == 0);

    onEvent(EV_STOP);
    EXPECT_EQ(3, cmdIdx);
    ASSERT_TRUE(strcmp(buf[2], "stop") == 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

