#include <mqtt_driver.h>
#include <send_state.h>
#include <receive_state.h>
#include <constants.h>
#include <wifi_driver.h>
#include "state_machine_coordinator.h"

StateMachineCoordinator::StateMachineCoordinator()
{
    setup_states();
}

StateMachineCoordinator &StateMachineCoordinator::get_instance()
{
    static StateMachineCoordinator instance;
    return instance;
}

const void StateMachineCoordinator::setup_states()
{
    //RECEIVE STATE
    stateMachine.addTransition(SEND, S_RECEIVE, S_SEND, set_state_to_send_coo);
    stateMachine.addTransition(RECEIVE, S_RECEIVE, S_RECEIVE, set_state_to_receive_coo);

    //SEND_STATE
    stateMachine.addTransition(SEND, S_SEND, S_SEND, set_state_to_send_coo);
    stateMachine.addTransition(RECEIVE, S_SEND, S_RECEIVE, set_state_to_receive_coo);
}

const void StateMachineCoordinator::loop()
{
    MqttDriver::get_instance().loop();
    stateMachine.raise(RECEIVE);
    MqttDriver::get_instance().loop();
    stateMachine.raise(SEND);
}
