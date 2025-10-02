#include "logging.hpp"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <syslog.h>
#include <unistd.h>

void log_event(const char *hostname, std::string event) {
  std::string log_file_path = "../../var/logs.txt";

  std::filesystem::path parent_dir =
      std::filesystem::path(log_file_path).parent_path();

  if (!std::filesystem::exists(parent_dir)) {
    std::filesystem::create_directories(parent_dir);
  }

  std::ofstream log_file(log_file_path, std::ios::app);
  if (!log_file.is_open()) {
    openlog(hostname, LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_ERR, "Failed to open log file: %s", log_file_path.c_str());
    closelog();
    return;
  }

  auto now = std::chrono::system_clock::now();
  auto t_c = std::chrono::system_clock::to_time_t(now);
  std::tm tm_struct;
  localtime_r(&t_c, &tm_struct);

  std::ostringstream oss;
  oss << std::put_time(&tm_struct, "%b %d %H:%M:%S");

  pid_t pid = getpid();
  std::string app_name = hostname;

  // Final log line
  log_file << oss.str() << " " << app_name << "[" << pid << "]: " << event
           << std::endl;

  log_file.close();
}
