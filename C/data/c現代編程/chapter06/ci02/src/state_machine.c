#include "state_machine.h"

void onStringOnState(StateMachine *pStateMachine, const BYTE *pInput, BYTE length) {
  BYTE i;
  for (i = 0; i < length; ++i) {
    onCharOnState(pStateMachine, pInput[i]);
  }
}

void onCharOnState(StateMachine *pStateMachine, BYTE c) {
  switch (pStateMachine->currentState) {
  case STATE_INIT:
    if (c == 'O') {
      pStateMachine->currentState = STATE_O;
    }
    else if (c == 'S') {
      pStateMachine->currentState = STATE_S;
    }
    else if (c == '\r' || c == '\n') {
      // Ignore.
    }
    else {
      pStateMachine->currentState = STATE_COMMAND_ERROR;
    }
    break;

  case STATE_O:
    if (c == 'N') {
      pStateMachine->currentState = STATE_ON_CHANNEL;
    }
    else if (c == 'F') {
      pStateMachine->currentState = STATE_OFF_CHANNEL;
    }
    else {
      pStateMachine->currentState = STATE_COMMAND_ERROR;
    }
    break;

  case STATE_S:
    if (c == 'T') {
      pStateMachine->currentState = STATE_CHECK_CHANNEL;
    }
    else {
      pStateMachine->currentState = STATE_COMMAND_ERROR;
    }
    break;

  case STATE_ON_CHANNEL:
    if ('0' <= c && c <= '1') {
      pStateMachine->currentState = STATE_ON;
      pStateMachine->channel = c - '0';
    }
    else {
      pStateMachine->currentState = STATE_OPERAND_ERROR;
    }
    break;

  case STATE_OFF_CHANNEL:
    if ('0' <= c && c <= '1') {
      pStateMachine->currentState = STATE_OFF;
      pStateMachine->channel = c - '0';
    }
    else {
      pStateMachine->currentState = STATE_OPERAND_ERROR;
    }
    break;
    
  case STATE_CHECK_CHANNEL:
    if ('0' <= c && c <= '1') {
      pStateMachine->currentState = STATE_CHECK;
      pStateMachine->channel = c - '0';
    }
    else {
      pStateMachine->currentState = STATE_OPERAND_ERROR;
    }
    break;

  case STATE_ON:
    if (c == '\r' || c == '\n') {
      pStateMachine->onCommand(pStateMachine->channel);
      pStateMachine->currentState = STATE_INIT;
    }
    else {
      pStateMachine->currentState = STATE_OPERAND_ERROR;
    }
    break;

  case STATE_OFF:
    if (c == '\r' || c == '\n') {
      pStateMachine->offCommand(pStateMachine->channel);
      pStateMachine->currentState = STATE_INIT;
    }
    else {
      pStateMachine->currentState = STATE_OPERAND_ERROR;
    }
    break;

  case STATE_CHECK:
    if (c == '\r' || c == '\n') {
      pStateMachine->stateCheckCommand(pStateMachine->channel);
      pStateMachine->currentState = STATE_INIT;
    }
    else {
      pStateMachine->currentState = STATE_OPERAND_ERROR;
    }
    break;

  case STATE_COMMAND_ERROR:
    if (c == '\r' || c == '\n') {
      pStateMachine->commandError();
      pStateMachine->currentState = STATE_INIT;
    }
    break;

  case STATE_OPERAND_ERROR:
    if (c == '\r' || c == '\n') {
      pStateMachine->operandError();
      pStateMachine->currentState = STATE_INIT;
    }
    break;
  }
}
