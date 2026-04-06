#include "command/Command.hpp"

Command::Command(const std::function<void(SceneNode& target, sf::Time& dt)>& action, const unsigned int& category)
: action(action)
, category(category) {}