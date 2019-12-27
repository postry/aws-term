/*
 * listtables.hpp
 *
 *  Created on: Dec. 24, 2019
 *      Author: elagon
 */

#ifndef COMMANDS_DYNAMO_LISTTABLES_HPP_
#define COMMANDS_DYNAMO_LISTTABLES_HPP_

#include "commands/command.hpp"

namespace app
{

namespace dynamo
{

//------------------------------------------------------------------------------
class ListTables : public Command
{
public:
    ListTables() = default;
    void execute(Args& args) override;
    virtual ~ListTables() = default;
};

} /* namespace dynamo */

} /* namespace app */

#endif /* COMMANDS_DYNAMO_LISTTABLES_HPP_ */
