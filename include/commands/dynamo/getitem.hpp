/*
 * getitem.hpp
 *
 *  Created on: Dec. 27, 2019
 *      Author: elagon
 */

#ifndef COMMANDS_DYNAMO_GETITEM_HPP_
#define COMMANDS_DYNAMO_GETITEM_HPP_

#include "commands/command.hpp"

namespace app
{

namespace dynamo
{

//------------------------------------------------------------------------------
class GetItem : public Command
{
public:
    void execute(Args& args) override;
};

} /* dynamo namespace */

} /* app namespace */

#endif /* COMMANDS_DYNAMO_GETITEM_HPP_ */
