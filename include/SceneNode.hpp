#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
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

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates) const ;
        virtual void draw_current(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        std::vector<Ptr> m_children;
        SceneNode* m_parent;
};
