#include "modbus.h"

Modbus::Modbus() {
  modbus_point.open("./test_file_output.csv",
                    std::ofstream::out | std::ofstream::app);
}

Modbus::~Modbus() {}

Modbus& Modbus::GetInstance() {
  static Modbus modbus;
  return modbus;
}

void Modbus::Save(int time) {
  std::cout << "save the file " << std::endl;
  modbus_point << time << std::endl;
  return;
}