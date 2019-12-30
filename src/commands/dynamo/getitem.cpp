/*
 * getitem.cpp
 *
 *  Created on: Dec. 27, 2019
 *      Author: elagon
 */

#include "commands/dynamo/getitem.hpp"
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <iostream>

namespace app
{
namespace dynamo
{

//------------------------------------------------------------------------------
void GetItem::execute(Args& args)
{
    const Aws::String region("ca-central-1");
    Aws::String table;
    Aws::String partitionKeyName;
    Aws::String partitionKeyValue;
    Aws::String sortKeyName;
    Aws::String sortKeyValue;
    Aws::String projection;
    args >> table >> partitionKeyName >> partitionKeyValue >> sortKeyName >> sortKeyValue;
    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = region;
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
    Aws::DynamoDB::Model::GetItemRequest req;
    req.SetTableName(table);
    Aws::DynamoDB::Model::AttributeValue partitionKey;
    partitionKey.SetS(partitionKeyValue);
    req.AddKey(partitionKeyName, partitionKey);

    // Add the sortKey only if not empty
    if (not sortKeyName.empty())
    {
        Aws::DynamoDB::Model::AttributeValue sortKey;
        sortKey.SetS(sortKeyValue);
        req.AddKey(sortKeyName, sortKey);
    }

    const Aws::DynamoDB::Model::GetItemOutcome& result = dynamoClient.GetItem(req);
    if (result.IsSuccess())
    {
        // Reference the retrieved fields/values
        const Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue>& item =
        result.GetResult().GetItem();
        if (item.size() > 0)
        {// Output each retrieved field and its value
            for (const auto& i : item)
            std::cout << i.first << ": " << i.second.GetS() << std::endl;
        }
        else
        {
            std::cout << "No item found with the key " << partitionKeyName << std::endl;
        }
    }
    else
    {
        std::cout << result.GetError() << std::endl;
    }
}

} /* dynamo namespace */

} /* app namespace */
