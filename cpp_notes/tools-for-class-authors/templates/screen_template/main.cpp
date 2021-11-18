#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include "screen.h"

int main() {
  Screen<5, 3> my_screen;
  my_screen.display(cout);
  my_screen.move(4, 0).set('#');
  return 0;
}