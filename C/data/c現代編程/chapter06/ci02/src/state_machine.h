#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "GenericTypeDefs.h"
#include "common.h"

typedef enum {
  STATE_INIT,
  STATE_O,
  STATE_S,
  STATE_ON_CHANNEL,
  STATE_ON,

  STATE_OFF_CHANNEL,
  STATE_OFF,

  STATE_CHECK_CHANNEL,
  STATE_CHECK,

  STATE_COMMAND_ERROR,
  STATE_OPERAND_ERROR
} State;

#ifdef __cplusplus
extern "C" {
#endif
  typedef void (*OnCommand)(BYTE channel);
  typedef void (*OffCommand)(BYTE channel);
  typedef void (*StateCheckCommand)(BYTE channel);
  typedef void (*CommandError)(void);
  typedef void (*OperandError)(void);
#ifdef __cplusplus
}
#endif

typedef struct {
  State currentState;
  BYTE channel;
  OnCommand onCommand;
  OffCommand offCommand;
  StateCheckCommand stateCheckCommand;
  CommandError commandError;
  OperandError operandError;
} StateMachine;

#define CREATE_STATE_MACHINE(                                            \
    onCommand, offCommand, stateCheckCommand, commandError, operandError \
) {                                                                      \
    STATE_INIT,                                                          \
    0,                                                                   \
    onCommand,                                                           \
    offCommand,                                                          \
    stateCheckCommand,                                                   \
    commandError,                                                        \
    operandError                                                         \
}

#ifdef __cplusplus
extern "C" {
#endif
  extern void onStringOnState(StateMachine *pStateMachine, const BYTE *pInput, BYTE length);
  extern void onCharOnState(StateMachine *pStateMachine, BYTE c);

#ifdef __cplusplus
}
#endif

#endif
