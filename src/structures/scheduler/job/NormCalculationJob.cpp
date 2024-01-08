
#include "../../../../headers/structures/scheduler/job/NormCalculationJob.h"
#include "../../../../headers/config/Logger.h"

void NormCalculationJob::execute() {
    LOG_INFO("Calculating square norm for point with id " );

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
        char buffer[50];
        sprintf(buffer, "Square norm for point with id %d is %f", point.getId(), squareNorm);
        LOG_INFO(buffer);

    }
}