#pragma once
#include "state_machine.h"
#include "state_machine_base.h"
class StateMachineEndNode : public StateMachineBase
{
public:
    static StateMachineEndNode &get_instance();
    StateMachineEndNode(StateMachineEndNode const &) = delete;
    void operator=(StateMachineEndNode const &) = delete;
    ~StateMachineEndNode() = default;

    const void loop() override;

private:
    StateMachineEndNode();
    //states used in the state machine.
    typedef enum
    {
        S_SLEEP,
        S_MEASURE,
        S_SEND,
        NUM_STATES,
    } state;

    //alphabet used by the state machine.
    typedef enum
    {
        SLEEP,
        MEASURE,
        SEND,
        NUM_SYMBOLS,
    } alphabet;
    typedef Bundle D;
    StateMachine<alphabet, state, D, NUM_SYMBOLS, NUM_STATES> stateMachine;
    Bundle bundle;
    const void setup_states() override;
};