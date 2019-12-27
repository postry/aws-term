/*
 * listusers.hpp
 *
 *  Created on: Dec. 26, 2019
 *      Author: elagon
 */

#ifndef COMMANDS_COGNITO_LISTUSERS_HPP_
#define COMMANDS_COGNITO_LISTUSERS_HPP_

#include "commands/command.hpp"

namespace app
{
namespace cognito
{

//------------------------------------------------------------------------------
class ListUsers : public Command
{
public:
    void execute(Args& args) override;
};

} /* namespace cognito */

} /* namespace app */

#endif /* COMMANDS_COGNITO_LISTUSERS_HPP_ */
