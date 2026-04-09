#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
namespace GUI {
    class Component:    public sf::Drawable,
                        public sf::Transformable,
                        public sf::NonCopyable {
        public:
            typedef std::shared_ptr<Component> Ptr;

        public:
            Component();

            virtual void activate();
            virtual void deactivate();
            bool is_activated();

            virtual bool is_selectable() const = 0;
            virtual void select();
            void deselect();
            bool is_selected() const;

            virtual void handle_events(const sf::Event& event) = 0;

        private:
            bool m_is_activated;
            bool m_is_selected;
    };
}
