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

void Neighbors::setDistance(float d) {
    this->distance = d;

}

void Neighbors::setId(int id) {
    this->id = id;
}

bool Neighbors::operator<(const Neighbors &other)  const {
    return distance < other.distance;
}

bool Neighbors::operator==(const Neighbors &other) const {
    // First, check if the base class (Point) is equal.
    if (!Point::operator==(other)) {
        return false;
    }

    // Then, compare the distance.
    return distance == other.distance;
}

void Neighbors::setFlag(bool flag) {
    this->flag = flag;
}

bool Neighbors::getFlag() const {
    return this->flag;
}

//bool Neighbors::operator>(const Neighbors &other) const {
//    if (!Point::operator>(other)) {
//        return false;
//    }
//    return distance > other.distance;
//}
