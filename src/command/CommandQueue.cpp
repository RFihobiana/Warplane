#include "command/CommandQueue.hpp"
#include "command/Command.hpp"

void CommandQueue::push_back(const Command& command) {
    m_data.push(command);
}

Command CommandQueue::pop() {
    Command command(m_data.front());
    m_data.pop();
    return command;
}

bool CommandQueue::is_empty() const {
    return m_data.empty();
}
