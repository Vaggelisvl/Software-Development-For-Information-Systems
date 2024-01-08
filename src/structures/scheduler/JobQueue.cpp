//
// Created by vaggelis on 3/1/2024.
//


#include "../../../headers/structures/scheduler/JobQueue.h"

void JobQueue::push(Job *job) {
    JobNode* node = new JobNode(job);
    if (back) {
        back->next = node;
    } else {
        front = node;
    }
    back = node;
}

Job *JobQueue::pop() {
    if (!front) return nullptr;
    JobNode* node = front;
    front = front->next;
    if (!front) back = nullptr;
    Job* job = node->job;
    delete node;
    return job;
}