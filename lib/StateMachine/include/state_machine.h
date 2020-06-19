#pragma once
#include <time.h>
#include <array>
#include <functional>
#include <type_traits>

template <typename T>
struct is_bool : public std::is_same<T, bool>
{
};

template <typename A, typename S, typename D, size_t A_num, size_t S_num>
class StateMachine
{
private:
    static constexpr bool checkStateType()
    {
        return (std::is_integral<S>::value || std::is_enum<S>::value) && !is_bool<S>::value;
    }

    static constexpr bool checkSymbolType()
    {
        return std::is_integral<A>::value || std::is_enum<S>::value;
    }

public:
    typedef A AlphabetType;
    typedef S StateType;
    typedef D *Data;
    typedef std::function<void()> HandlerType;
    typedef std::function<void(Data d)> DataHandlerType;
    static_assert(checkStateType(), "State type should be integral or enum!");
    static_assert(checkSymbolType(), "Symbol type should be integral or enum!");

    struct StateTransition
    {
        HandlerType handler;
        StateType target;
    };
    struct DataStateTransition
    {
        DataHandlerType handler;
        StateType target;
    };

    void addTransition(AlphabetType symbol, StateType from, StateType to, HandlerType handler)
    {
        StateTransition t{handler, to};
        this->stateTypes[from][symbol] = std::move(t);
    }

    void addTransition(AlphabetType symbol, StateType from, StateType to, DataHandlerType handler)
    {
        DataStateTransition t{handler, to};
        this->dataStateTypes[from][symbol] = std::move(t);
    }

    //Please keep in mind that the correct raise function needs to be called.
    //Functions added with DataHandlerType need to be called *with* Data&
    //Functions added with HandlerType need to be called *without* Data&
    void raise(AlphabetType symbol)
    {
        StateTransition &ref = this->stateTypes[this->currentStateType][symbol];
        ref.handler();
        this->currentStateType = ref.target;
    }

    //Please keep in mind that the correct raise function needs to be called.
    //Functions added with DataHandlerType need to be called *with* Data&
    //Functions added with HandlerType need to be called *without* Data&
    void raise(AlphabetType symbol, D *data)
    {
        DataStateTransition &ref = this->dataStateTypes[this->currentStateType][symbol];
        ref.handler(data);
        this->currentStateType = ref.target;
    }

private:
    std::array<std::array<StateTransition, A_num>, S_num> stateTypes;
    std::array<std::array<DataStateTransition, A_num>, S_num> dataStateTypes;
    StateType currentStateType;
};