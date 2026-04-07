#pragma once
#include "states/StateStack.hpp"
#include <memory>

template<typename T>
void StateStack::register_state(const States::ID id) {
    m_factories[id] = [this] () { 
        return std::unique_ptr<T>(new T(*this, m_context));
    };
}
