#include <string>
#include <syslog.h>
#include <filesystem>
#include <exception>
#include <system_error>

void create_fake_devices()
{
     std::string device_bus = "../../System/sys/bus/i2c/devices/i2c-3";
     std::string device = "../../System/sys/bus/i2c/devices/3-0040";

     std::error_code ec;

     if(!std::filesystem::exists(device_bus))
     {
          try
          {
               std::filesystem::create_directories(device_bus,ec);
               if (ec)
        {
            openlog("device_manager", LOG_PID | LOG_CONS, LOG_USER);
            syslog(LOG_ERR, "Failed to create device_bus: %s: ERROR: %s", device_bus.c_str(), ec.message().c_str());
            closelog();
        }
          }
          catch(std::exception& e)
          {
                   openlog("device_manager", LOG_PID | LOG_CONS, LOG_USER);
                    syslog(LOG_ERR, "Failed to create device_bus: %s: ERROR: %s", device_bus.c_str(), e.what());
               closelog();
          }
     }

     if(!std::filesystem::exists(device))
     {
          try
          {
               std::filesystem::create_directories(device,ec);
               if (ec)
        {
            openlog("device_manager", LOG_PID | LOG_CONS, LOG_USER);
            syslog(LOG_ERR, "Failed to create device_bus: %s: ERROR: %s", device_bus.c_str(), ec.message().c_str());
            closelog();
        }
          }
          catch(std::exception& e)
          {
                   openlog("device_manager", LOG_PID | LOG_CONS, LOG_USER);
                    syslog(LOG_ERR, "Failed to create device: %s: ERROR: %s", device.c_str(), e.what());
               closelog();
          }
     }
}