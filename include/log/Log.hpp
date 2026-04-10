#pragma once

#include <string>
#include <vector>

class Log {
    public:
        virtual void add(const std::string& log);
        const std::vector<std::string>& get_texts() const;

    private:
        std::vector<std::string> m_texts;
};
