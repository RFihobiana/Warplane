#include "GUI/Component.hpp"

namespace GUI {

    // Activated
    Component::Component()
    : m_is_activated(false) {}

    void Component::activate() {
        m_is_activated = true;
    }

    void Component::deactivate() {
        m_is_activated = false;
    }

    bool Component::is_activated() {
        return m_is_activated;
    }

    // Selected
    void Component::select() {
        m_is_selected = true;
    }

    void Component::deselect() {
        m_is_selected = false;
    }

    bool Component::is_selected() const {
        return m_is_selected;
    }
}
