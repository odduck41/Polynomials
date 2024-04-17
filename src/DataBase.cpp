#include "../include/DataBase.h"

void DataBase::erase(size_t index) {
    polynomials.erase(index);
}

Polynomial& DataBase::operator[](size_t index) {
    return polynomials[index];
}

void DataBase::insert(const Polynomial& p) {
    polynomials.insert_tail(p);
}