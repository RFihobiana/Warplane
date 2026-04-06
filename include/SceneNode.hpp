#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

struct Command;

class SceneNode: public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
    public:
        typedef std::unique_ptr<SceneNode> Ptr;
    
    public:
        SceneNode();

        void attach_child(Ptr child);
        Ptr dettach_child(const SceneNode& node);

        void update(sf::Time& dt);

        sf::Transform   get_world_transform()   const;
        sf::Vector2f    get_world_position()    const;

        virtual unsigned int get_category() const;

        void on_command(const Command& command, sf::Time& dt);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates) const ;
        virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void update_current(sf::Time& dt);
        void update_children(sf::Time& dt);

    private:
        std::vector<Ptr> m_children;
        SceneNode* m_parent;
};
