#include "List.h"
#include "Polynomial.h"

class DataBase {
  public:
    DataBase() = default;
    void erase(size_t);
    Polynomial& operator[](size_t);
    void insert(const Polynomial&);
  private:
    List<Polynomial> polynomials;
};