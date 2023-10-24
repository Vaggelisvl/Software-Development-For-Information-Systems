//
// Created by e.vrailas on 24/10/2023.
//

#include "../../../headers/structures/unorderedMap/KeyValue.h"
KeyValue::KeyValue(int k, const int &v)  : key(k), value(v), next(nullptr) {
    LOG_INFO("KeyValue Node with value "+to_string(v)+" has been created ");
}

KeyValue *KeyValue::getNext() const {
    return next;
}

int KeyValue::getKey() const {return key}
const int &KeyValue::getValue() const {
    return value;
}

void KeyValue::setNext(KeyValue *n) {next=n;}