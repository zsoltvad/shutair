#include "pulse-generator.h"

const std::string getPulse(unsigned long controllerId, unsigned int controllerChannel, std::string controllerCommand) {
  std::string id = getIdAsPulse(controllerId);
  std::string channel = getChannelAsPulse(controllerChannel);
  std::string command = getCommandAsPulse(controllerCommand);


  std::string tail = controllerCommand != "program" ? "14" : "04";

  return "32" + id + channel + "01" + command + tail;
}

const std::string getIdAsPulse(unsigned long controllerId) {
  return toPulse(std::bitset<28>(controllerId).to_string());
}

const std::string getChannelAsPulse(unsigned int controllerChannel) {
  return toPulse(std::bitset<4>(controllerChannel).to_string());
}

const std::string getCommandAsPulse(std::string controllerCommand) {
  std::map<std::string, std::string> commandToBinaryMap;
  commandToBinaryMap["up"] = "001000";
  commandToBinaryMap["down"] = "011001";
  commandToBinaryMap["stop"] = "101010";
  commandToBinaryMap["program"] = "100110";
  
  return toPulse(commandToBinaryMap.at(controllerCommand));
}

const std::string toPulse(std::string binary) {
  std::map<char, std::string> binaryToPulseMap;
  binaryToPulseMap['0'] = "01";
  binaryToPulseMap['1'] = "10";

  std::string pulse = "";

  for (auto it = binary.cbegin() ; it != binary.cend(); ++it) {
    pulse += binaryToPulseMap.at(*it);
  }

  return pulse;
}
