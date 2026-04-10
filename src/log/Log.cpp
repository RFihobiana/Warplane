#include "log/Log.hpp"
#include <string>
#include <vector>

void Log::add(const std::string& log) {
    m_texts.push_back(log);
}

const std::vector<std::string>& Log::get_texts() const {
    return m_texts; 
}
