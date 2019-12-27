/*
 * putitem.hpp
 *
 *  Created on: Dec. 27, 2019
 *      Author: elagon
 */

#ifndef COMMANDS_DYNAMO_PUTITEM_HPP_
#define COMMANDS_DYNAMO_PUTITEM_HPP_

#include "commands/command.hpp"

namespace app
{
namespace dynamo
{

//------------------------------------------------------------------------------
class PutItem : public Command
{
public:
    void execute(Args& args) override;
};

} /* dynamo namespace */

} /* app namespace */

#endif /* COMMANDS_DYNAMO_PUTITEM_HPP_ */
