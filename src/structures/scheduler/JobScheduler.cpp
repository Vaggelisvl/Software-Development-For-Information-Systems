//
// Created by vaggelis on 3/1/2024.
//

#include "JobScheduler.h"
#include <pthread.h>
JobScheduler::JobScheduler(int numThreads) : numThreads(numThreads), stop(false) {
    threads = new pthread_t[numThreads];
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);

    for (int i = 0; i < numThreads; ++i) {
        pthread_create(&threads[i], nullptr, [](void* arg) -> void* {
            JobScheduler* scheduler = static_cast<JobScheduler*>(arg);
            while (true) {
                pthread_mutex_lock(&scheduler->mutex);
                while (!scheduler->stop && scheduler->queue.empty()) {
                    pthread_cond_wait(&scheduler->cond, &scheduler->mutex);
                }
                if (scheduler->stop && scheduler->queue.empty()) {
                    pthread_mutex_unlock(&scheduler->mutex);
                    return nullptr;
                }
                Job* job = scheduler->queue.pop();
                pthread_mutex_unlock(&scheduler->mutex);
                job->execute();
                delete job;
            }
        }, this);
    }
}

JobScheduler::~JobScheduler() {
    pthread_mutex_lock(&mutex);
    stop = true;
    pthread_mutex_unlock(&mutex);
    pthread_cond_broadcast(&cond);
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], nullptr);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    delete[] threads;
}

void JobScheduler::submit(Job *job) {
    pthread_mutex_lock(&mutex);
    queue.push(job);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
}