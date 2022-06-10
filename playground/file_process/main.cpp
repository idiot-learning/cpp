#include "modbus.h"
int main() {
  for (int i = 0; i < 5; i++) {
    Modbus::GetInstance().Save(1);
  }

  return 0;
}