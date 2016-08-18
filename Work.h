#ifndef Work_H
#define Work_H

#include <node.h>
#include <node_object_wrap.h>
#include <string>
#include <vector>
#include <map>
#include"Thread_Data.h"
#include <uv.h>
using namespace v8;
using namespace std;
namespace WaDirectorywrapAsynchro_data_v8 {
class Work {
public:
  
  Work(){};
  ~Work(){};

  uv_work_t  request;

  Persistent<Function> callback;

  vector<std::string> liste;

  Thread_Data Output_Data;
  
  vector<Thread_Data> Intra_Data;

  vector<Thread_Data> Input_Data;

};
}
#endif;