#include "GenericTypeDefs.h"
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <gtest/gtest.h>

#include "state_machine.h"

typedef struct {
  const char *pMethodName;
  union {
    struct {
      BYTE channel;
    } onCommandArg;

    struct {
      BYTE channel;
    } offCommandArg;

    struct {
      BYTE channel;
    } stateCheckCommandArg;
  };
} History;

static std::vector<History *> history;

static void clearHistory() {
  for (std::vector<History *>::iterator z = history.begin(); z != history.end(); ++z) {
    delete *z;
  }

  history.clear();
}

extern "C" {
  static void onCommand(BYTE channel) {
    History *pHis = new History();
    pHis->pMethodName = "onCommand";
    pHis->onCommandArg.channel = channel;
    history.push_back(pHis);
  }

  static void offCommand(BYTE channel) {
    History *pHis = new History();
    pHis->pMethodName = "offCommand";
    pHis->offCommandArg.channel = channel;
    history.push_back(pHis);
  }

  static void stateCheckCommand(BYTE channel) {
    History *pHis = new History();
    pHis->pMethodName = "stateCheckCommand";
    pHis->stateCheckCommandArg.channel = channel;
    history.push_back(pHis);
  }

  static void commandError(void) {
    History *pHis = new History();
    pHis->pMethodName = "commandError";
    history.push_back(pHis);
  }

  static void operandError(void) {
    History *pHis = new History();
    pHis->pMethodName = "operandError";
    history.push_back(pHis);
  }
}

static StateMachine *createStateMachine() {
  StateMachine *p = (StateMachine *)malloc(sizeof(StateMachine));
  StateMachine sm = CREATE_STATE_MACHINE(onCommand, offCommand, stateCheckCommand, commandError, operandError);
  memcpy(p, &sm, sizeof(StateMachine));
  return p;
}

TEST(StateMachineTest, onCommand) {
  StateMachine *p = createStateMachine();

  EXPECT_EQ(STATE_INIT, p->currentState);

  onStringOnState(p, (BYTE *)"ON", 2);
  EXPECT_EQ(STATE_ON_CHANNEL, p->currentState);
  EXPECT_EQ((size_t)0, history.size());

  onStringOnState(p, (BYTE *)"0", 1);
  EXPECT_EQ(STATE_ON, p->currentState);
  EXPECT_EQ((size_t)0, history.size());

  onCharOnState(p, '\r');
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());
  EXPECT_EQ(0, strcmp("onCommand", history[0]->pMethodName));
  EXPECT_EQ((BYTE)0, history[0]->onCommandArg.channel);

  onCharOnState(p, '\n');
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());

  free(p);
  clearHistory();
}

TEST(StateMachineTest, offCommand) {
  StateMachine *p = createStateMachine();

  EXPECT_EQ(STATE_INIT, p->currentState);

  onStringOnState(p, (BYTE *)"OF", 2);
  EXPECT_EQ(STATE_OFF_CHANNEL, p->currentState);
  EXPECT_EQ((size_t)0, history.size());

  onStringOnState(p, (BYTE *)"1", 1);
  EXPECT_EQ(STATE_OFF, p->currentState);
  EXPECT_EQ((size_t)0, history.size());

  onCharOnState(p, '\n');
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());
  EXPECT_EQ(0, strcmp("offCommand", history[0]->pMethodName));
  EXPECT_EQ((BYTE)1, history[0]->offCommandArg.channel);

  free(p);
  clearHistory();
}

TEST(StateMachineTest, otherCharacterIsIgnored) {
  StateMachine *p = createStateMachine();

  EXPECT_EQ(STATE_INIT, p->currentState);

  onStringOnState(p, (BYTE *)"\r\n", 2);
  EXPECT_EQ(STATE_INIT, p->currentState);

  free(p);
  clearHistory();
}

TEST(StateMachineTest, commandError1) {
  StateMachine *p = createStateMachine();

  onStringOnState(p, (BYTE *)"ABC\n", 4);
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());
  EXPECT_EQ(0, strcmp("commandError", history[0]->pMethodName));

  free(p);
  clearHistory();
}

TEST(StateMachineTest, commandError2) {
  StateMachine *p = createStateMachine();

  onStringOnState(p, (BYTE *)"OA\r\n", 4);
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());
  EXPECT_EQ(0, strcmp("commandError", history[0]->pMethodName));

  free(p);
  clearHistory();
}

TEST(StateMachineTest, commandError3) {
  StateMachine *p = createStateMachine();

  onStringOnState(p, (BYTE *)"SA\r\n", 4);
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());
  EXPECT_EQ(0, strcmp("commandError", history[0]->pMethodName));

  free(p);
  clearHistory();
}

TEST(StateMachineTest, operandError) {
  StateMachine *p = createStateMachine();

  onStringOnState(p, (BYTE *)"ON-\n", 4);
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());
  EXPECT_EQ(0, strcmp("operandError", history[0]->pMethodName));

  free(p);
  clearHistory();
}

TEST(StateMachineTest, operandError2) {
  StateMachine *p = createStateMachine();

  onStringOnState(p, (BYTE *)"ON2\r\n", 5);
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());
  EXPECT_EQ(0, strcmp("operandError", history[0]->pMethodName));

  free(p);
  clearHistory();
}

TEST(StateMachineTest, operandError3) {
  StateMachine *p = createStateMachine();
 
  onStringOnState(p, (BYTE *)"OF-\r", 4);
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());
  EXPECT_EQ(0, strcmp("operandError", history[0]->pMethodName));

  free(p);
  clearHistory();
}

TEST(StateMachineTest, operandError4) {
  StateMachine *p = createStateMachine();
  onStringOnState(p, (BYTE *)"OF2\n", 4);
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());
  EXPECT_EQ(0, strcmp("operandError", history[0]->pMethodName));

  free(p);
  clearHistory();
}

TEST(StateMachineTest, operandError5) {
  StateMachine *p = createStateMachine();
  onStringOnState(p, (BYTE *)"ST2\n", 4);
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());
  EXPECT_EQ(0, strcmp("operandError", history[0]->pMethodName));

  free(p);
  clearHistory();
}

TEST(StateMachineTest, operandError6) {
  StateMachine *p = createStateMachine();
  onStringOnState(p, (BYTE *)"ON1a\n", 5);
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());
  EXPECT_EQ(0, strcmp("operandError", history[0]->pMethodName));

  free(p);
  clearHistory();
}

TEST(StateMachineTest, operandError7) {
  StateMachine *p = createStateMachine();
  onStringOnState(p, (BYTE *)"OF1a\n", 5);
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());
  EXPECT_EQ(0, strcmp("operandError", history[0]->pMethodName));

  free(p);
  clearHistory();
}

TEST(StateMachineTest, operandError8) {
  StateMachine *p = createStateMachine();
  onStringOnState(p, (BYTE *)"ST1a\n", 5);
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());
  EXPECT_EQ(0, strcmp("operandError", history[0]->pMethodName));

  free(p);
  clearHistory();
}

TEST(StateMachineTest, stateCheck) {
  StateMachine *p = createStateMachine();

  EXPECT_EQ(STATE_INIT, p->currentState);

  onStringOnState(p, (BYTE *)"ST0\r\n", 4);
  EXPECT_EQ(STATE_INIT, p->currentState);
  EXPECT_EQ((size_t)1, history.size());
  EXPECT_EQ(0, strcmp("stateCheckCommand", history[0]->pMethodName));
  EXPECT_EQ((BYTE)0, history[0]->stateCheckCommandArg.channel);

  free(p);
  clearHistory();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
