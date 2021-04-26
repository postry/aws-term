/*
 * listthings.cpp
 *
 *  Created on: Feb. 29, 2020
 *      Author: elagon
 */

#include "commands/iot/listthings.hpp"
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/iot/IoTClient.h>
#include <aws/iot/model/ListThingsRequest.h>
#include <aws/iot/model/ListThingsResult.h>

namespace app
{
namespace iot
{

void ListThings::execute(Args& args)
{
    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = "ca-central-1";

    Aws::IoT::IoTClient iotClient(clientConfig);

    Aws::IoT::Model::ListThingsRequest ltr;
    const Aws::IoT::Model::ListThingsOutcome& lto = iotClient.ListThings(ltr);
    if (!lto.IsSuccess())
    {
        std::cout << "Error: " << lto.GetError().GetMessage() << std::endl;
        return;
    }
    for (const auto& t : lto.GetResult().GetThings())
        std::cout << t.GetThingName() << std::endl;
}

} /* iot namespace */

} /* app namespace */
