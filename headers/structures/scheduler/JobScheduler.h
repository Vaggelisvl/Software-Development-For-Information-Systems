/**
 * @file JobScheduler.h
 * @brief This file contains the declaration of the JobScheduler class.
 */
#ifndef JOBSCHEDULER_H
#define JOBSCHEDULER_H


#include <csignal>
#include "job/Job.h"
#include "JobQueue.h"

class JobScheduler {
private:
    double *waitingTime; ///< Array to store the waiting time of each job.
    double *executionTime; ///< Array to store the execution time of each job.
    JobQueue queue; ///< Queue of jobs to be executed.
    pthread_t *threads; ///< Array of threads that execute the jobs.
    int numThreads; ///< Number of threads in the pool.
    pthread_mutex_t mutex; ///< Mutex for synchronizing access to the queue.
    pthread_cond_t cond; ///< Condition variable for signaling threads about available jobs.
    bool stop; ///< Flag to indicate whether the scheduler should stop.
    int *jobCount; ///< Array to store the number of jobs executed by each thread.
    int numJobs = 0; ///< Total number of jobs submitted to the scheduler.

public:

    /**
     * @brief Constructor for the JobScheduler class.
     * @param numThreads The number of threads in the pool.
     */
    explicit JobScheduler(int numThreads = 5);


    /**
     * @brief Function that each thread executes.
     * @param arg The argument passed to the thread function.
     */
    static void *threadFunction(void *arg);

    /**
        * @brief Destructor for the JobScheduler class.
        */
    ~JobScheduler();

    /**
     * @brief Function to print statistics about job execution.
     */
    void printStats();

    /**
   * @brief Function to start executing jobs.
   */
    void start_execute();

    /**
    * @brief Function to stop the scheduler and wait for all jobs to finish.
    */
    void finish_all();

    /**
    * @brief Function to wait for all jobs to finish.
    */
    void wait_to_finish();

    /**
    * @brief Function to submit a new job to the scheduler.
    * @param job The job to be submitted.
    */
    void submit(Job *job);
};

#endif
