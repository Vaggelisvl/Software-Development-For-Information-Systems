#include "../../../headers/structures/point/Neighbors.h"
Neighbors::Neighbors(int id, float distance, Vector<float> coordinates) {
    this->id = id;
    this->distance = distance;
    this->coordinates = coordinates;
//    LOG_INFO("Neighbor has been created!");
}

Neighbors::Neighbors() :distance(0) {
    this->id = 0;
//    LOG_INFO("Neighbor has been created!");
}

int Neighbors::getId() const {
    return this->id;
}

float Neighbors::getDistance() const {
    return this->distance;
}

void Neighbors::setDistance(float distance) {
    this->distance = distance;

}

void Neighbors::setId(int id) {
    this->id = id;
}

bool Neighbors::operator<(const Neighbors &other)  const {
    return distance < other.distance;
}