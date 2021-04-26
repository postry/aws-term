/*
 * updatething.hpp
 *
 *  Created on: Mar. 1, 2020
 *      Author: elagon
 */

#ifndef COMMANDS_IOT_UPDATETHING_HPP_
#define COMMANDS_IOT_UPDATETHING_HPP_

#include "commands/command.hpp"

namespace app
{

namespace iot
{

class UpdateThing: public Command
{
public:
    void execute(Args& args) override;
};

} /* iot namespace */

} /* app namespace */

#endif /* COMMANDS_IOT_UPDATETHING_HPP_ */
