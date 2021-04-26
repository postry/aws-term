/*
 * updatething.cpp
 *
 *  Created on: Mar. 1, 2020
 *      Author: elagon
 */

#include "commands/iot/updatething.hpp"
#include <iostream>
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/iot-data/IoTDataPlaneClient.h>
#include <aws/iot-data/model/GetThingShadowRequest.h>
#include <aws/iot-data/model/GetThingShadowResult.h>
#include <aws/iot-data/model/UpdateThingShadowRequest.h>
#include <aws/iot-data/model/UpdateThingShadowResult.h>
#include <aws/core/utils/stream/PreallocatedStreamBuf.h>
#include <aws/core/utils/stream/SimpleStreamBuf.h>

namespace app
{

namespace iot
{

void UpdateThing::execute(Args& args)
{
    Aws::String thingName = "LPC54018";
//    args >> userName;
    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = "ca-central-1";
    Aws::IoTDataPlane::IoTDataPlaneClient iotClient(clientConfig);

    // First get shadow
    Aws::IoTDataPlane::Model::GetThingShadowRequest gtsr;
    gtsr.SetThingName(thingName);
    Aws::IoTDataPlane::Model::GetThingShadowOutcome lto = iotClient.GetThingShadow(gtsr);
    if (!lto.IsSuccess())
    {
        std::cout << "Error: " << lto.GetError().GetMessage() << std::endl;
        return;
    }
    else
    {

    auto input = R"({
    "state":    {
        "desired":  {
            "postryIOT0":   "red",
            "welcome":  "POSTRY"
        },
        "reported": {
            "postryIOT0":   "red",
            "welcome":  "suka"
        }
    }
}
)";

        Aws::Utils::Json::JsonValue doc(input);


//        std::cout << "Get Success" << std::endl;
//        Aws::Utils::Json::JsonValue jsonPayload (lto.GetResult().GetPayload());
//        std::cout <<  jsonPayload.View().WriteReadable() << std::endl;
//
//        jsonPayload.View().GetObject("state").GetObject("desired");
//
//
//        Aws::Utils::Json::JsonValue desired;
//        desired.WithString("TEST","TEST");
//        desired.WithString("postryIOT0","red");
//        desired.WithString("welcome","TEST");
//
//        Aws::Utils::Json::JsonValue state;
//        state.WithObject("desired" , desired);

        // Update shadow
        Aws::IoTDataPlane::Model::UpdateThingShadowRequest request;
        request.SetThingName(thingName);

//        auto& pl = lto.GetResult().GetPayload();
//        jsonPayload.WithObject("state", state);



        Aws::Utils::Stream::SimpleStreamBuf sbuf(input);
//        Aws::IOStream ioStream(&streamBuf);

        std::shared_ptr<Aws::IOStream>  body = std::shared_ptr<Aws::IOStream>( new Aws::IOStream(&sbuf));
//        body->clear();
//        Aws::Utils::Json::JsonValue jsonPayload2;
//        jsonPayload2.WithString("state", "{\"TEST\":\"POSTRY\"}");


        request.SetBody(body);
//        doc
//        *request.GetBody() << doc.View().WriteCompact();
        Aws::IoTDataPlane::Model::UpdateThingShadowOutcome rsp = iotClient.UpdateThingShadow(request);
        if (!rsp.IsSuccess())
        {
            std::cout << "Error: " << rsp.GetError().GetMessage() << std::endl;
            return;
        }
        else
        {
            std::cout << "Update Success" << std::endl;
            rsp.GetResult().GetPayload();
            std::cout <<  Aws::Utils::Json::JsonValue(rsp.GetResult().GetPayload()).View().WriteReadable() << std::endl;

        }
    }
};

} /* iot namespace */

} /* app namespace */
