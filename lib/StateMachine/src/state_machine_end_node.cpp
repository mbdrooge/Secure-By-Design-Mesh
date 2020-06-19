#include <sleep_state.h>
#include <measure_state.h>
#include <send_state.h>
#include "state_machine_end_node.h"

StateMachineEndNode::StateMachineEndNode()
{
    setup_states();
}

StateMachineEndNode &StateMachineEndNode::StateMachineEndNode::get_instance()
{
    static StateMachineEndNode instance;
    return instance;
}

const void StateMachineEndNode::setup_states()
{
    //SLEEP STATE
    stateMachine.addTransition(SLEEP, S_SLEEP, S_SLEEP, set_state_to_sleep);
    stateMachine.addTransition(MEASURE, S_SLEEP, S_MEASURE, set_state_to_measure);
    stateMachine.addTransition(SEND, S_SLEEP, S_SEND, set_state_to_send);

    //MEASURE STATE
    stateMachine.addTransition(SLEEP, S_MEASURE, S_SLEEP, set_state_to_sleep);
    stateMachine.addTransition(MEASURE, S_MEASURE, S_MEASURE, set_state_to_measure);

    //SEND STATE
    stateMachine.addTransition(SLEEP, S_SEND, S_SLEEP, set_state_to_sleep);
    stateMachine.addTransition(SEND, S_SEND, S_SEND, set_state_to_send);

    //set initial state to sleep
    stateMachine.raise(SLEEP);
}

const void StateMachineEndNode::loop()
{
    stateMachine.raise(MEASURE, &this->bundle);
    stateMachine.raise(SLEEP);
    stateMachine.raise(SEND, &this->bundle);
    stateMachine.raise(SLEEP);
}