#pragma once

#include "entity/Player.hpp"
#include "resources/ResourceIdentifier.hpp"
#include "states/StateIdentification.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>

class StateStack;
class State {
    public:
        typedef std::unique_ptr<State> Ptr;

        struct Context {
            sf::RenderWindow*   window;
            TextureHolder*      textures;
            FontHolder*         fonts;
            Player*             player;

            Context(
                sf::RenderWindow&   window,
                TextureHolder&      textures,
                FontHolder&         fonts,
                Player&             player
            )
            : window(&window)
            , textures(&textures)
            , fonts(&fonts)
            , player(&player) {}
        };
        
    public:
        State(StateStack& stack, Context& ctx);

        virtual void draw() const = 0;
        virtual bool update(sf::Time& dt) = 0;
        virtual bool handle_events(const sf::Event& event) = 0;

    protected:
        Context get_context() const;
        void request_pop();
        void request_clear();
        void request_push(const States::ID& state_id);
        
    private:
        StateStack& m_stack;
        Context     m_context;    
};
