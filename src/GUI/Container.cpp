#include "GUI/Container.hpp"
#include "GUI/Component.hpp"

namespace GUI {
    Container::Container(): m_selected_child(-1) {}

    bool  Container::is_selectable() const { return false; }

    void Container::pack(Component::Ptr component) {
        if(!has_selection() && component->is_selectable())
            m_selected_child = m_children.size();
        
        m_children.push_back(component);
    }

    bool Container::has_selection() const {
        return m_selected_child > -1;
    }

    void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        for(const auto& child: m_children) {
            target.draw(*child, states);
        }
    }
}
