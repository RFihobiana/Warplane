#pragma once

#include "GUI/Component.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
namespace GUI {
    class Component: public sf::Drawable,
                    public sf::Transformable,
                    private sf::NonCopyable
    {
        public:
            typedef std::shared_ptr<Component> Ptr;

        public:
            Component();

            virtual void select();
            virtual void deselect();
            bool is_selected();
            virtual bool is_selectable() const = 0;

            virtual void activate();
            virtual void deactivate();
            bool is_active();

            virtual void handle_events(const sf::Event& event) = 0;

        private:
            bool m_is_selected;
            bool m_is_active;
    };
}
