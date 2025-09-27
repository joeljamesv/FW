#include "commandcenter.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool actions(std::string action) {
  std::vector<std::string> vectors = {"get", "set"};

  for (std::string it : vectors) {
    if (it == action) {
      return true;
    }
  }

  return false;
}

bool properties(std::string property) {
  std::vector<std::string> vectors = {"state"};

  for (std::string it : vectors) {
    if (it == property) {
      return true;
    }
  }

  return false;
}

bool targets(std::string target) {
  std::vector<std::string> vectors = {"firefly"};

  for (std::string it : vectors) {
    if (it == target) {
      return true;
    }
  }

  return false;
}

bool values(std::string value) {
  std::vector<std::string> vectors = {"off", "on"};

  for (std::string it : vectors) {
    if (it == value) {
      return true;
    }
  }

  return false;
}

bool process_command(std::string command) {
  std::string action;
  std::string target;
  std::string value;
  std::string property;

  std::stringstream ss(command);

  if (!std::getline(ss, action, ':')) {
    return false;
  }
  if (!std::getline(ss, target, ':')) {
    return false;
  }
  if (!std::getline(ss, property, ':')) {
    return false;
  }
  if (!std::getline(ss, value, ':')) {
    return false;
  }

  return actions(action) && targets(target) && properties(property) &&
         values(value);
}
