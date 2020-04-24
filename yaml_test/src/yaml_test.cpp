#include "rclcpp/rclcpp.hpp"
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <fstream>
#include "ament_index_cpp/get_package_share_directory.hpp"

int main(int argc, char *argv[]){
  rclcpp::init(argc, argv);

  //std::string fin = "../script/test_yaml.yaml";
  const std::string package_name = "yaml_test";
  auto position = ament_index_cpp::get_package_share_directory(package_name);

  std::cout<<position<<std::endl;

  std::string fin = "/script/test_yaml.yaml";

  std::string fullPath = position + fin;

  std::cout<<fullPath<<std::endl;

  YAML::Node yamlConfig = YAML::LoadFile(fullPath);
  
  int int_param = yamlConfig["int_param"].as<int>();
  std::cout<< "int_param is " << int_param << std::endl;
  std::cout << "  node size: " << yamlConfig.size() << std::endl;
  std::cout << yamlConfig["bool_param"].as<bool>() << "\n";

  std::ofstream fout(position+"/script/save_file.yaml");
  fout << yamlConfig;

  rclcpp::shutdown();
  return 0;
}
