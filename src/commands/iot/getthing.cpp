/*
 * getthing.cpp
 *
 *  Created on: Feb. 29, 2020
 *      Author: elagon
 */

#include "commands/iot/getthing.hpp"
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/iot-data/IoTDataPlaneClient.h>
#include <aws/iot-data/model/GetThingShadowRequest.h>
#include <aws/iot-data/model/GetThingShadowResult.h>

namespace app
{
namespace iot
{

void GetThing::execute(Args& args)
{
    Aws::String userName;
    args >> userName;

    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = "ca-central-1";

    Aws::IoTDataPlane::IoTDataPlaneClient iotClient(clientConfig);

    Aws::IoTDataPlane::Model::GetThingShadowRequest gtsr;
    gtsr.SetThingName(userName);
    Aws::IoTDataPlane::Model::GetThingShadowOutcome lto = iotClient.GetThingShadow(gtsr);
    if (!lto.IsSuccess())
    {
        std::cout << "Error: " << lto.GetError().GetMessage() << std::endl;
        return;
    }

    else
    {
        std::cout << "Success" << std::endl;

        Aws::Utils::Json::JsonValue jsonPayload (lto.GetResult().GetPayload());
        for (const auto& kv : jsonPayload.View().GetAllObjects())
            std::cout << kv.first <<           std::endl;

        std::cout <<  jsonPayload.View().WriteReadable() << std::endl;
    }
}

} /* iot namespace */

} /* app namespace */
