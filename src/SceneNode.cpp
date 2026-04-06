#include "SceneNode.hpp"
#include "command/Category.hpp"
#include "command/Command.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <cassert>
#include <utility>
#include <algorithm>

SceneNode::SceneNode()
: m_children()
, m_parent(nullptr) {}

void SceneNode::attach_child(SceneNode::Ptr child) {
    child->m_parent = this;
    m_children.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::dettach_child(const SceneNode& node) {
    const auto found = std::find_if(m_children.begin(), m_children.end(), [&node](Ptr& child) -> bool {
        return child.get() == &node;
    });

    assert(found != m_children.end());

    Ptr result(std::move(*found));
    result->m_parent = nullptr;
    m_children.erase(found);

    return result;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    draw_current(target, states);
    for(auto& child: m_children) 
        child->draw(target, states);
}

void SceneNode::draw_current(sf::RenderTarget& target, sf::RenderStates states) const {}

void SceneNode::update(sf::Time& dt) {
    update_current(dt);
    update_children(dt);
}

void SceneNode::update_current(sf::Time& dt) {}

void SceneNode::update_children(sf::Time& dt) {
    for(auto& child: m_children) {
        child->update(dt);
    }
}

sf::Transform SceneNode::get_world_transform() const {
    sf::Transform transform(sf::Transform::Identity);

    for(const SceneNode* node = this; node != nullptr; node = node->m_parent)
        transform = node->getTransform() * transform;

    return transform;
}

sf::Vector2f SceneNode::get_world_position() const {
    return get_world_transform() * sf::Vector2f();
}

unsigned int SceneNode::get_category() const {
    return Category::Scene;
}

void SceneNode::on_command(const Command& command, sf::Time& dt) {
    if(get_category() & command.category) command.action(*this, dt);
    
    for(auto& child: m_children) {
        child->on_command(command, dt);
    }
}
