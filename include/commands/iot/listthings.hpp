/*
 * listthings.hpp
 *
 *  Created on: Feb. 29, 2020
 *      Author: elagon
 */

#ifndef COMMANDS_IOT_LISTTHINGS_HPP_
#define COMMANDS_IOT_LISTTHINGS_HPP_

#include "commands/command.hpp"

namespace app
{
namespace iot
{

class ListThings : public Command
{
public:
    void execute(Args& args) override;
};

} /* iot namespace */

} /* app namespace */

#endif /* COMMANDS_IOT_LISTTHINGS_HPP_ */
