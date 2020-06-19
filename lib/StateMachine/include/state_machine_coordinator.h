#pragma once
#include "state_machine.h"
#include "state_machine_base.h"
#include <bundle.h>

class StateMachineCoordinator : public StateMachineBase
{
public:
    static StateMachineCoordinator &get_instance();
    StateMachineCoordinator(StateMachineCoordinator const &) = delete;
    void operator=(StateMachineCoordinator const &) = delete;
    ~StateMachineCoordinator() = default;

    const void loop() override;

private:
    StateMachineCoordinator();
    //states used in the state machine.
    typedef enum
    {
        S_SEND,
        S_RECEIVE,
        NUM_STATES,
    } state;

    //alphabet used by the state machine.
    typedef enum
    {
        SEND,
        RECEIVE,
        NUM_SYMBOLS,
    } alphabet;
    typedef Bundle D;
    StateMachine<alphabet, state, D, NUM_SYMBOLS, NUM_STATES> stateMachine;
    const void setup_states() override;
};