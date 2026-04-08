#include "states/ParallelTask.hpp"
#include <SFML/System/Lock.hpp>

const float TASK_DURATION = 6.5f;

ParallelTask::ParallelTask()
: m_thread(&ParallelTask::run_task, this)
, m_is_finished(false) {}

void ParallelTask::execute() {
    m_thread.launch();
}

bool ParallelTask::is_finished() {
    sf::Lock lock(m_mutex);
    return m_is_finished;
}

float ParallelTask::get_completion() {
    sf::Lock lock(m_mutex);
    return m_elapsed_time.getElapsedTime().asSeconds() / TASK_DURATION;
}

void ParallelTask::run_task() {
    bool ended = false;
    while(!ended) {
        sf::Lock lock(m_mutex);
        if(m_elapsed_time.getElapsedTime().asSeconds() >= TASK_DURATION) {
            ended = true;
        }
    }

    {
        sf::Lock lock(m_mutex);
        m_is_finished = true;
    }
}

