//
// Created by vaggelis on 3/1/2024.
//

#include "../../../headers/config/Logger.h"
#include "../../../headers/structures/scheduler/JobScheduler.h"
#include <pthread.h>
#include <cstdio>
#include <sys/resource.h>
#include <cstdlib>
#include <unistd.h>

struct ThreadArg {
    JobScheduler* scheduler;
    int threadIndex;
};
JobScheduler::JobScheduler(int numThreads) : numThreads(numThreads), stop(false) {
    waitingTime = new double[numThreads]();
    executionTime = new double[numThreads]();
    jobCount = new int[numThreads]();
    this->threads = new pthread_t[numThreads];
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);
    char log[100];
    sprintf(log, "JobScheduler created with %d threads", numThreads);
    LOG_INFO( log);
}

JobScheduler::~JobScheduler() {
    delete[] waitingTime;
    finish_all();
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    delete[] jobCount;
    delete[] threads;
}



void JobScheduler::finish_all() {
    pthread_mutex_lock(&mutex);
    stop = true;
    pthread_mutex_unlock(&mutex);
    pthread_cond_broadcast(&cond);
}

void JobScheduler::wait_to_finish() {
    // Lock the mutex before accessing the shared data
    pthread_mutex_lock(&mutex);
    // Set the stop flag to true
    stop = true;
    // Unlock the mutex before signaling the condition variable
    pthread_mutex_unlock(&mutex);
    // Signal all waiting threads
    pthread_cond_broadcast(&cond);
    // Wait for all threads to finish
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], nullptr);
    }
}

void JobScheduler::submit(Job *job){
//    job->incrementJobId();
    pthread_mutex_lock(&mutex);
    queue.push(job);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&cond);
    char log[100];
    sprintf(log, "Job with id %d submitted", numJobs++);
    LOG_INFO( log);

}

void JobScheduler::printStats() {
    for (int i = 0; i < numThreads; ++i) {
        char log[150];
        sprintf(log, "Thread %d executed %d jobs | Waiting Time: %f |, Execution Time: %f", i, jobCount[i], waitingTime[i],executionTime[i]);
        LOG_INFO( log);
    }
    char log[150];

    sprintf(log,"Number of processors: %ld | Page size: %ld | Physical memory: %ld\n ", sysconf(_SC_NPROCESSORS_ONLN), sysconf(_SC_PAGESIZE),sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE));
//    printf("Page size: %ld\n", sysconf(_SC_PAGESIZE));
//    printf("Physical memory: %ld\n", sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE));
    LOG_INFO( log);
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    sprintf(log, "CPU memory usage: %ld kB | RAM usage: %ld kB\n", usage.ru_maxrss, usage.ru_ixrss);
    LOG_INFO( log);

}
void *JobScheduler::threadFunction(void *arg) {
    ThreadArg* threadArg = static_cast<ThreadArg*>(arg);
    JobScheduler* scheduler = threadArg->scheduler;
    int threadIndex = threadArg->threadIndex;
    while (true) {
        pthread_mutex_lock(&scheduler->mutex);
        while (!scheduler->stop && scheduler->queue.empty()) {
            clock_t startWait = clock();
            pthread_cond_wait(&scheduler->cond, &scheduler->mutex);
            clock_t endWait = clock();
            scheduler->waitingTime[threadIndex] += static_cast<double>(endWait - startWait) / CLOCKS_PER_SEC;
        }
        if (scheduler->stop && scheduler->queue.empty()) {
            pthread_mutex_unlock(&scheduler->mutex);
            return nullptr;
        }
        Job* job = scheduler->queue.pop();
        if (job->areDependenciesMet()) {
            scheduler->jobCount[threadIndex]++;
            pthread_mutex_unlock(&scheduler->mutex);
            clock_t startExecution = clock();
            bool executed = job->run();
            clock_t endExecution = clock();
            scheduler->executionTime[threadIndex] += static_cast<double>(endExecution - startExecution) / CLOCKS_PER_SEC;
            if (!executed) {
                pthread_mutex_lock(&scheduler->mutex);
                scheduler->queue.push(job);
                pthread_mutex_unlock(&scheduler->mutex);
                pthread_cond_signal(&scheduler->cond);
            } else {
                delete job;
                pthread_cond_broadcast(&scheduler->cond); // Signal all threads that a job has completed
            }
        } else {
            scheduler->queue.push(job);
            pthread_mutex_unlock(&scheduler->mutex);
            usleep(1000); // Sleep for a short period of time to give other jobs a chance to complete
        }
    }
}

void JobScheduler::start_execute() {
    this->threads = new pthread_t[numThreads];
    ThreadArg* args = new ThreadArg[numThreads];
    for (int i = 0; i < numThreads; ++i) {
        args[i].scheduler = this;
        args[i].threadIndex = i;
        pthread_create(&threads[i], nullptr, JobScheduler::threadFunction, &args[i]);
    }


}

void JobScheduler::printSchedulerState() {
    char log[300];
    sprintf(log, "JobScheduler State: \nNumber of Jobs: %d\nNumber of Threads: %d\nJobs in Queue: %d\n", numJobs, numThreads, queue.getSize());
    LOG_INFO( log);

    while(!queue.empty()){
        Job* job = queue.pop();
        job->printJobState();
        queue.push(job);
    }


    // Print state of each thread
    for (int i = 0; i < numThreads; ++i) {
        char log1[300];
        sprintf(log, "Thread %d State: \nJobs Executed: %d\nWaiting Time: %f\nExecution Time: %f\n", i, jobCount[i], waitingTime[i],executionTime[i]);
        LOG_INFO( log1);
    }
}
