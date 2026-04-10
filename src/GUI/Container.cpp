#include "GUI/Container.hpp"
#include "GUI/Component.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

namespace GUI {
    Container::Container(): m_selected_child(-1) {}

    bool  Container::is_selectable() const { return false; }

    void Container::handle_events(const sf::Event& event) {
        if(has_selection() && m_children[m_selected_child]->is_active()) {
            m_children[m_selected_child]->handle_events(event);
        }
        
        else if(event.type == sf::Event::KeyReleased) {
            if(
                event.key.code == sf::Keyboard::Up
                || event.key.code == sf::Keyboard::W
            ) select_prev();

            if(
                event.key.code == sf::Keyboard::Down
                || event.key.code == sf::Keyboard::S
            ) select_next();

            if(
                event.key.code == sf::Keyboard::Return
                || event.key.code == sf::Keyboard::Space
                || event.key.code == sf::Keyboard::E
            ) {
                if(has_selection()) m_children[m_selected_child]->activate();
            }
        }
    }

    void Container::select_at(const int index) {
        if(!m_children[index]->is_selectable()) return;

        std::ranges::for_each(m_children, [](auto& child) {
            child->deselect();
        });
        
        m_selected_child = index;
        m_children[m_selected_child]->select();
    }

    void Container::select_prev() {
        if(!has_selection()) return;

        int prev = m_selected_child;
        do {
            prev = (prev + 1) % m_children.size();
        } while(!m_children[prev]->is_selectable());

        select_at(prev);
    }

    void Container::select_next() {
        if(!has_selection()) return;

        int next = m_selected_child;
        do {
            next = (next + 1) % m_children.size();
        } while(!m_children[next]->is_selectable());

        select_at(next);
    }

    void Container::pack(Component::Ptr component) {
        if(!has_selection() && component->is_selectable()) {
            m_selected_child = m_children.size();
            component->select();
        }
        
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
