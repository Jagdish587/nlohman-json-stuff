#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

#include <vector>
using namespace std;
using json = nlohmann::json;



struct person {
  std::string name;
  std::string address;
  int age;
};


void to_json(json& j_struct, const person& p) {
  j_struct = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
}

void from_json(const json& j_struct, person& p) {
  j_struct.at("name").get_to(p.name);
  j_struct.at("address").get_to(p.address);
  j_struct.at("age").get_to(p.age);
}

void readjsonFile()
{
  std::ifstream myfile("myjsoncode.json");

  //create a json oneject and parse the file
  json myjsonobj = json::parse(myfile);

  // even easier with structured bindings (C++17)
  cout<<"priniting using c++ 17 \n";
  for (auto& [key, value] : myjsonobj.items()) {
    cout<<"************ start ************** \n\n";
    std::cout << key << " : " << value << endl;
    cout<<"\n*************** end ******************** \n\n";
  }

  // print appName
  string mystr = myjsonobj["common"]["appName"].get<std::string>();
  cout<<"appName = "<<myjsonobj["common"]["appName"]<<endl;
  cout<<"mystr = "<<mystr<<endl;

  // print sdk version
  string sdkVersion = myjsonobj["common"]["sdkversion"].get<std::string>();
  cout<<"sdk version = "<<sdkVersion<<endl;

  //print dependecy
  // std::array<string, 2> dependencey = myjsonobj["common"]["dependencey"]["testServices"].get<std::array<std::string, int>();
  // cout<<"dependencey  = "<<dependencey<<endl;

  cout<<"dependecy = "<<myjsonobj["common"]["dependencey"]<<endl;

  std::vector<string> myvector = myjsonobj["common"]["dependencey"]["testServices"].get<vector<string>>();
  cout<<"vector valaues 0 "<<myvector[0]<<endl;
  cout<<"vector valaues 1 "<<myvector[1]<<endl;

  std::map<string,std::vector<string>> mymap =  myjsonobj["common"]["dependencey"];


  for (auto &myitkeys : mymap) {
    cout<<myitkeys.first<<" :";

    for (auto &it : myitkeys.second) {
      cout<<" "<<it<<" ";
    }
  }

  vector<string> mytestServices;


  for(auto &it: myjsonobj["common"]["dependencey"]["testServices"]) {
    mytestServices.push_back(it);
  }

  cout<<endl;
  cout<<"mytestServices using vector [0] = "<<mytestServices[0]<<endl;
  cout<<"mytestServices using vector [1] = "<<mytestServices[1]<<endl;

  //  cout<<"mytestServices values[0] = "<<myjsonobj["common"]["dependencey"]["mytestServices"][0]<<endl;
  // cout<<"mytestServices values[1] = "<<myjsonobj["common"]["dependencey"]["mytestServices"][1]<<endl;


  // lets print appServices stuff

  // cout<<"appServices = "<<myjsonobj["appServices"]["windows"]["screen"]<<endl;

  vector<vector<string>> screens_supported ;

  for(auto &mit : myjsonobj["appServices"]["MyService"]["windows"]) {

    for(auto it: mit)
      screens_supported.push_back(it);
  }


  cout<<"screens supported = ";
  for(auto &scit: screens_supported) {
    for (auto &it : scit) {
      cout<<it<<" ";

    }
  }
  cout<<endl;


  for (auto const &stringVector : screens_supported) {
    auto it = std::find(std::begin(stringVector), std::end(stringVector), "FRONT_CENTRE");
    if (it != std::end(stringVector)) {
      // do what you want
      cout<<"found value front_centre "<<*it<<" at pos = "<<it - stringVector.begin()<<endl;
      break;
    }
  }

}

void cppstyletest()
{
  // vector example
  std::vector<int> myvector {2,5,8,7};
  json j_vector(myvector);

  for(auto &it: j_vector) {
    cout<<"vector value = "<<it<<" ";
  }

  std::map<string, int> mymap { {"Jagdish",25}, {"Hello",23}, {"MObis",46} };
  json j_map(mymap);

  for(auto &it: mymap) {
    cout<<"key = "<<it.first<<", value = "<<it.second<<endl;
  }


  // fetch str values
  string str = "Hello world , I am Jagdish Tirumala ok ";
  json j_str = str;

  string getstr = j_str.get<std::string>();

  cout<<"getstr = "<<getstr<<endl;

  bool b1 = false;
  json j_boolvalue = b1;

  bool myBoolVal = j_boolvalue.get<bool>();

  cout<<"myBoolVal val = "<<myBoolVal<<endl;

  // numbers

  int val = 45;
  json j_num = val;
  int intVal = j_num.get<int>();
  cout<<"intVal = "<<intVal<<endl;

  double pi = 3.14;
  json j_double = pi ;
  double myDoubleVal = j_double.get<double>();
  cout<<"myDoubleVal = "<<myDoubleVal<<endl;

}



void structstyletest()
{

  const person structPerson {"Jagdish", "LB Nagar", 16};

  json j_struct;
  to_json(j_struct, structPerson);

  person rxPerson ;

  from_json(j_struct,rxPerson);

  cout<<"rxPerson : name = "<<rxPerson.name<<" address = "<<rxPerson.address<<" age = "<<rxPerson.age<<endl;

}


int main()
{


  // compile this file as g++ main.cpp -std=c++1z -o main
  // read file from json
  cout<<endl;
  readjsonFile();
  cout<<endl;

  // some other stuff
  cppstyletest();
  cout<<endl;
  structstyletest();
  cout<<endl;

  return 0;
}
