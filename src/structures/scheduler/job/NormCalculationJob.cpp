
#include "../../../../headers/structures/scheduler/job/NormCalculationJob.h"
#include "../../../../headers/config/Logger.h"
void NormCalculationJob::execute() {


    for (int i=0;i <this->points.getSize();i++) {
        pthread_rwlock_rdlock(&this->graphInitialization->pointslock);
        Vector<float> coordinates = this->points.at(i).getCoordinates();
        pthread_rwlock_unlock(&this->graphInitialization->pointslock);
        float squareNorm = 0.0;
        for (float coordinate : coordinates) {
            squareNorm += coordinate * coordinate;
        }
        // Store the square norm for later use
        pthread_rwlock_wrlock(&this->graphInitialization->pointslock);
        this->points.at(i).setSquareNorm(squareNorm);
        pthread_rwlock_unlock(&this->graphInitialization->pointslock);

//        char buffer[100];
//        sprintf(buffer, "Square norm for point with id %d is %f", this->points.at(i).getId(), this->graphInitialization->getPoints().at(i).getSquareNorm());
//        LOG_INFO(buffer);
    }

}

NormCalculationJob::NormCalculationJob(Vector<Point> points, int id,GraphInitialization* graphInitialization) {
    this->points = points;
    this->setJobId(id);
    this->graphInitialization=graphInitialization;
//    char buffer[50];
//    sprintf(buffer, "NormCalculationJob created with id %d", id);
//    LOG_INFO(buffer);
}
