#pragma once

class StateMachineBase
{
public:
    virtual const void loop() = 0;

protected:
    virtual const void setup_states() = 0;
};