#include <fstream>
#include <iostream>
#include <filesystem>

void log_event(std::string event)
{
     std::string log_file_path="../var/logs";

     std::string parent_directory= std::filesystem::path(log_file_path).parent_path();
     if(!std::filesystem::exists(parent_directory))
     {
          std::filesystem::create_directories(parent_directory);
     }

     std::ofstream log_file(log_file_path,std::ios::app);
     if(!log_file.is_open())
     {
          std::cerr<<"file not opened";
          return;
     }
     
     log_file << event <<std::endl;

     log_file.close();
}