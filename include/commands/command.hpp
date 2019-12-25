/*
 * Command.hpp
 *
 *  Created on: Dec. 24, 2019
 *      Author: elagon
 */

#ifndef COMMANDS_COMMAND_HPP_
#define COMMANDS_COMMAND_HPP_

#include <memory>
#include <sstream>

namespace app
{

using Args = std::stringstream;

class Command
{
public:
    using Ptr = std::unique_ptr<Command>;

    Command() = default;

    virtual void execute(Args& args) = 0;

    virtual ~Command() = default;
};

} /* namespace app */

#endif /* COMMANDS_COMMAND_HPP_ */
