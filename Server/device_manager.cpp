#include <exception>
#include <filesystem>
#include <fstream>
#include <string>
#include <syslog.h>
#include <system_error>

void create_fake_devices() {
  std::string device_bus_path = "../../System/sys/bus/i2c/devices/i2c-3";
  std::string device = "../../System/sys/bus/i2c/devices/3-0040";

  std::error_code ec;

  if (!std::filesystem::exists(device_bus_path)) {
    try {
      std::filesystem::create_directories(device_bus_path, ec);
      if (ec) {
        openlog("device_manager", LOG_PID | LOG_CONS, LOG_USER);
        syslog(LOG_ERR, "Failed to create device_bus: %s: ERROR: %s",
               device_bus_path.c_str(), ec.message().c_str());
        closelog();
        return;
      }
    } catch (std::exception &e) {
      openlog("device_manager", LOG_PID | LOG_CONS, LOG_USER);
      syslog(LOG_ERR, "Failed to create device_bus: %s: ERROR: %s",
             device_bus_path.c_str(), e.what());
      closelog();
      return;
    }
  }

  if (!std::filesystem::exists(device)) {
    try {
      std::filesystem::create_directories(device, ec);
      if (ec) {
        openlog("device_manager", LOG_PID | LOG_CONS, LOG_USER);
        syslog(LOG_ERR, "Failed to create device_bus: %s: ERROR: %s",
               device.c_str(), ec.message().c_str());
        closelog();
        return;
      }
    } catch (std::exception &e) {
      openlog("device_manager", LOG_PID | LOG_CONS, LOG_USER);
      syslog(LOG_ERR, "Failed to create device: %s: ERROR: %s", device.c_str(),
             e.what());
      closelog();
      return;
    }
  }
  std::string device_name = device + "/name";
  std::string device_modalias = device + "/modalias";
  std::string device_addr = device + "/address";
  std::string device_bus = device + "/bus";

  std::ofstream(device_name) << "led";
  std::ofstream(device_modalias) << "i2c:firefly";
  std::ofstream(device_addr) << "0x40";
  std::ofstream(device_bus) << "i2c";
}