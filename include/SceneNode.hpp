#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
class SceneNode: public sf::Drawable, public sf::Transformable, private sf::NonCopyable {
    public:
        typedef std::unique_ptr<SceneNode> Ptr;
    
    public:
        SceneNode();

        void attach_child(Ptr child);
        Ptr dettach_child(const SceneNode& node);

        void update(sf::Time& dt);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates) const ;
        virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;

        virtual void update_current(sf::Time& dt);
        void update_children(sf::Time& dt);

    private:
        std::vector<Ptr> m_children;
        SceneNode* m_parent;
};
