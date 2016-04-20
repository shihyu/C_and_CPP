#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

typedef struct LowPriorityInterrupt {
    unsigned int (* const isUsartInterruptOccurred)(struct LowPriorityInterrupt *pThis);
    void (* const onUsartInterrupt)(struct LowPriorityInterrupt *pThis);
    int (* const isTimer3Overflow)(struct LowPriorityInterrupt *pThis);
    void (* const onTimer3Interrupt)(struct LowPriorityInterrupt *pThis);
    // ...
} LowPriorityInterrupt;

void performLowPriorityInterrupt(LowPriorityInterrupt *pThis);

#endif
