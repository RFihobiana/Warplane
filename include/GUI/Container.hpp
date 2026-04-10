#pragma once

#include "GUI/Component.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <memory>
#include <vector>
namespace GUI {

    class Container: public Component {
        public:
            typedef std::shared_ptr<Container> Ptr;

        public:
            Container();

            virtual bool is_selectable() const;
            virtual void handle_events(const sf::Event& event);

            void pack(Component::Ptr component);

        private:
            bool has_selection() const;

            void select_at(const int index);
            void select_prev();
            void select_next();
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        private:
            std::vector<Component::Ptr> m_children;
            int m_selected_child;
    };

}
