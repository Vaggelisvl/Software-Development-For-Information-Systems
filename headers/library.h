#ifndef _PROJECT_LIBRARY_H
#define _PROJECT_LIBRARY_H

#include <iostream>
#include <fstream>

#include "../headers/structures/vector/Vector.h"
#include "../headers/config/Logger.h"
#include "../headers/structures/point/Point.h"
#include "../headers/config/Logger.h"
#include "../headers/structures/GraphInitialization.h"

uint32_t readVectorFromFile(const char* , Vector<Point>& );
#endif //_PROJECT_LIBRARY_H
