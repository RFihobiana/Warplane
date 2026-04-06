#pragma once

#include "command/Command.hpp"
#include <queue>

class CommandQueue {
    public:
        void push_back(const Command& command);
        Command pop();
        bool is_empty() const;

    private:
        std::queue<Command> m_data;
};
