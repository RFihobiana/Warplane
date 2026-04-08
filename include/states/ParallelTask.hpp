#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Thread.hpp>
class ParallelTask {
    public:
        ParallelTask();
        void execute();

        bool is_finished();
        float get_completion();

    private:
        void run_task();
    
    private:
        sf::Thread  m_thread;
        bool        m_is_finished;
        sf::Mutex   m_mutex;
        sf::Clock   m_elapsed_time;
};
