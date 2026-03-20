#ifndef PULSE_GENERATOR_H
#define PULSE_GENERATOR_H

#include <bitset>
#include <iostream>
#include <map>

const std::string getPulse(unsigned long controllerId, unsigned int controllerChannel, std::string controllerCommand);

const std::string getIdAsPulse(unsigned long controllerId);

const std::string getChannelAsPulse(unsigned int controllerChannel);

const std::string getCommandAsPulse(std::string controllerCommand);

const std::string toPulse(std::string binary);

#endif
