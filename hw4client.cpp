
// ecs36b first program

#include <iostream>
#include "Shadow_Thing.h"

using namespace std;

int
main()
{
  Shadow_Thing st_1 { "http://127.0.0.1:8384", "Thing", "00000001" };
  Json::Value result = st_1.dump2JSON();
  return 0;
}
