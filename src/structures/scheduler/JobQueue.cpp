//
// Created by vaggelis on 3/1/2024.
//


#include "../../../headers/structures/scheduler/JobQueue.h"
#include "../../../headers/config/Logger.h"



void JobQueue::push(Job *job) {
    auto *node = new JobNode(job);
    if (back) {
        back->next = node;
    } else {
        front = node;
    }
    back = node;
    size++;
//    char log[35];
//    sprintf(log, "JobQueue::push");
//    LOG_INFO( log);
}

Job *JobQueue::pop() {
    if (!front) return NULL;
    JobNode *node = front;
    front = front->next;
    if (!front) back = NULL;
    Job *job = node->job;
    delete node;
    size--;
    return job;
}

Job *JobQueue::peek() { return front ? front->job : NULL; }

int JobQueue::getSize() {
    return size;
}

JobNode *JobQueue::begin() {
    return front;
}

