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

            void pack(Component::Ptr component);

        private:
            bool has_selection() const;
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        private:
            std::vector<Component::Ptr> m_children;
            int m_selected_child;
    };

}
