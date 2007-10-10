#include "tseries.hpp"

int main() {
  TSeries<double,double> x(1000,10);

  x.copy();

  return 1;
}
  
