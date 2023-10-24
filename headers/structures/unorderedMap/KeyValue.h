//
// Created by e.vrailas on 24/10/2023.
//

#ifndef PROJECT_2023_1_KEYVALUE_H
#define PROJECT_2023_1_KEYVALUE_H

#include <string>
#include "../../../headers/config/Logger.h"
class KeyValue {
public:
    KeyValue(int k, const std::string& v);
    int getKey() const;
    const std::string& getValue() const ;
    KeyValue* getNext() const ;
    void setNext(KeyValue* n) ;

private:
    int key;
    std::string value;
    KeyValue* next;
};


#endif //PROJECT_2023_1_KEYVALUE_H
