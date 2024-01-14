
#include "../../../../headers/structures/scheduler/job/NormCalculationJob.h"
#include "../../../../headers/config/Logger.h"

void NormCalculationJob::execute() {

    // Implement the logic for calculating the square norm of points here
    for (auto& point : points) {
        Vector<float> coordinates = point.getCoordinates();
        float squareNorm = 0.0;
        for (float coordinate : coordinates) {
            squareNorm += coordinate * coordinate;
        }
        // Store the square norm for later use
        // Assuming Point class has a method setSquareNorm for this purpose
        const_cast<Point&>(point).setSquareNorm(squareNorm);

        LOG_INFO(([&](){char* buffer = new char[100];sprintf(buffer, "Square norm for point with id %d is %f", point.getId(), squareNorm);return buffer;})());
    }
    char buffer[60];
    sprintf(buffer, "-----------NormCalculationJob completed-----------------");
    LOG_INFO(buffer);

}

NormCalculationJob::NormCalculationJob(Vector<Point> points, int id) {
    this->points = points;
    this->setJobId(id);
    char buffer[50];
    sprintf(buffer, "NormCalculationJob created with id %d", id);
    LOG_INFO(buffer);
}
