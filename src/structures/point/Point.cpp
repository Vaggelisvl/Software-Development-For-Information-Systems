//
// Created by snz on 10/31/2023.
//

#include "../../../headers/structures/point/Point.h"
#include "../../../headers/config/Logger.h"
Point::Point(int id, Vector<float> coordinates) : id(id), coordinates(coordinates) {
    LOG_INFO("Point has been created!");
}

Point::Point():id(0) {
    LOG_INFO("Point has been created!");
}

int Point::getId() const {
    return this->id;
}

Vector<float> Point::getCoordinates() const {
    return this->coordinates;
}

void Point::setCoordinates(Vector<float> coordinates) {
    this->coordinates = coordinates;
}

void Point::setId(int id) {
    this->id = id;
}

