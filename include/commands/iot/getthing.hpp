/*
 * getthing.hpp
 *
 *  Created on: Feb. 29, 2020
 *      Author: elagon
 */

#ifndef COMMANDS_IOT_GETTHING_HPP_
#define COMMANDS_IOT_GETTHING_HPP_

#include "commands/command.hpp"

namespace app
{
namespace iot
{

class GetThing: public Command
{
public:
    void execute(Args& args) override;
};

} /* iot namespace */

} /* app namespace */

#endif /* COMMANDS_IOT_GETTHING_HPP_ */
