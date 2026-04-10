#include "GUI/Logger.hpp"
#include "GUI/Label.hpp"
#include "resources/ResourceIdentifier.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cstddef>
#include <memory>
#include <sstream>
#include <string>

namespace GUI {
    Logger::Logger(TextureHolder& textures, FontHolder& fonts)
    : m_textures(textures)
    , m_fonts(fonts)
    , m_bg_rect(sf::Vector2f(500, 1024)) {
        m_bg_rect.setFillColor(sf::Color(0, 0, 0, 64));
    }

    bool Logger::is_selectable() const {
        return false;
    }

    void Logger::add(const std::string& log) {

        // Process Log: auto \n
        const int MAX_LINE_CHARS = 40;
        std::stringstream processed_log;
        for(size_t i = 0; i < log.length(); i++) {
            processed_log << log[i];
            if(i > 0 && i % (MAX_LINE_CHARS - 1) == 0) processed_log << '\n';
        }

        Log::add(processed_log.str());
        static const float scale = 0.6f;
        Label::Ptr label(std::make_shared<Label> (m_fonts, processed_log.str()));
        label->setScale(scale, scale);
        label->setPosition(
            10.f,
            m_labels.size() * 40.f
        );
        m_labels.push_back(label);
    }

    void Logger::handle_events(const sf::Event& event) {}

    void Logger::set_bg_size(const sf::Vector2f size) {
        m_bg_rect.setSize(size);
    }

    void Logger::set_bg_size(const float width, const float height) {
        m_bg_rect.setSize(sf::Vector2f(width, height));
    }

    void Logger::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();

        target.draw(m_bg_rect, states);

        for(const auto& label: m_labels) {
            target.draw(*label, states);
        }
    }
}
