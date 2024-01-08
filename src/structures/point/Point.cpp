//
// Created by snz on 10/31/2023.
//

#include "../../../headers/structures/point/Point.h"
#include "../../../headers/config/Logger.h"

Point::Point(int id, Vector<float> coordinates) : id(id), coordinates(coordinates)
{
    //    LOG_INFO("Point has been created!");
}

Point::Point() : id(0)
{
    //    LOG_INFO("Point has been created!");
}

void Point::setHasBeenChoosen(int hasBeenChoosen)
{
    this->hasBeenChoosen = hasBeenChoosen;
}

int Point::getId() const
{
    return this->id;
}

Vector<float> Point::getCoordinates() const
{
    return this->coordinates;
}

void Point::setCoordinates(Vector<float> coordinates)
{
    this->coordinates = coordinates;
}

void Point::setId(int id)
{
    this->id = id;
}

Point::Point(Point const& point)
{
    this->id = point.getId();
    this->coordinates = point.getCoordinates();
}

int Point::getHasBeenChoosen() const
{
    return hasBeenChoosen;
}

bool Point::operator==(const Point& other) const
{
    return this->id == other.id;
}

size_t Point::customHash() const
{
    // Use a combination of the ID and coordinates to create a custom hash
    size_t hashValue = static_cast<size_t>(getId());
    for (const float& coord : coordinates)
    {
        hashValue = hashValue * 31 + static_cast<size_t>(coord);
    }
    return hashValue;
}

size_t Point::hashValue() const
{
    return customHash();
}

bool Point::operator<(const Point& other) const
{
    return this->id < other.id;
}

bool Point::operator>(const Point& other) const
{
    return this->id > other.id;
}

void Point::setSquareNorm(float squareNorm) {
    Point::squareNorm = squareNorm;
}
