#pragma once

#include "command/Command.hpp"
#include "command/CommandQueue.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>
class Player {
    /* This class give an order to player's aircraft */
    public:
        enum Action {
            MoveLeft,
            MoveRight,
            MoveUp,
            MoveDown,

            ShowPosition,

            Fire,
            LaunchMissile,
            
            ActionCount,
        };

    public:
        Player();
        void handle_event(const sf::Event& event, CommandQueue& commands);
        void handle_realtime_event(CommandQueue& commands);

        void assign_key(const sf::Keyboard::Key& key, const Action& action);
        sf::Keyboard::Key get_assigned_key(const Action& action) const;

    private:
        static bool is_realtime_action(const Action& action);
    
    private:
        std::unordered_map<sf::Keyboard::Key, Action>   m_key_binding;
        std::unordered_map<Action, Command>             m_action_binding;
};
