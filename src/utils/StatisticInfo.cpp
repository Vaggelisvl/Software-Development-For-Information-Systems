//
// Created by snz on 11/26/2023.
//

#include <cstdio>
#include "../../headers/utils/StatisticInfo.h"

StatisticInfo::StatisticInfo() {
    this->rightDecision = 0;
    this->wrongDecision = 0;
    this->total = 0;
    this->percentage = 0;

}

void StatisticInfo::increaseRightDecision() {

    this->rightDecision++;

}

void StatisticInfo::increaseWrongDecision() {
    this->wrongDecision++;

}

void StatisticInfo::increaseTotal() {
    this->total++;

}

int StatisticInfo::getRightDecision() {
    return this->rightDecision;
}

int StatisticInfo::getWrongDecision() {
    return this->wrongDecision;
}

int StatisticInfo::getTotal() {
    return this->total;
}

int StatisticInfo::getPercentage() {
    return this->percentage;
}

void StatisticInfo::calculatePercentage() {
    this->percentage = (this->rightDecision * 100) / this->total;

}

void StatisticInfo::printStatistics() {
    printf("Right Decisions: %d\n", this->rightDecision);
    printf("Wrong Decisions: %d\n", this->wrongDecision);
    printf("Total Decisions: %d\n", this->total);
    printf("Percentage: %d\n", this->percentage);

}

void StatisticInfo::reset() {
    this->rightDecision = 0;
    this->wrongDecision = 0;
    this->total = 0;
    this->percentage = 0;

}

void StatisticInfo::increaseRightDecisions(int i) {
    this->rightDecision += i;

}

void StatisticInfo::increaseWrongDecisions(int i) {
    this->wrongDecision += i;

}

void StatisticInfo::increaseTotals(int i) {
    this->total += i;

}
