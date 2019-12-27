/*
 * createtable.hpp
 *
 *  Created on: Dec. 27, 2019
 *      Author: elagon
 */

#ifndef COMMANDS_DYNAMO_CREATETABLE_HPP_
#define COMMANDS_DYNAMO_CREATETABLE_HPP_

#include "commands/command.hpp"

namespace app
{

namespace dynamo
{

//------------------------------------------------------------------------------
class CreateTable : public Command
{
public:
    void execute(Args& args) override;
};

} /* namespace dynamo */

} /* namespace app */

#endif /* COMMANDS_DYNAMO_CREATETABLE_HPP_ */
