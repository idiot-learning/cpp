#include <fstream>
#include <iostream>

class Modbus {
 public:
  static Modbus &GetInstance();
  ~Modbus();

  std::ofstream modbus_point;

  Modbus(Modbus &) = delete;
  Modbus &operator=(Modbus &) = delete;
  void Save(int time);

 private:
  Modbus();
};