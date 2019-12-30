/*
 * deleteitem.cpp
 *
 *  Created on: Dec. 27, 2019
 *      Author: elagon
 */

#include "commands/dynamo/deleteitem.hpp"
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/DeleteItemRequest.h>
#include <iostream>

namespace app
{
namespace dynamo
{

//------------------------------------------------------------------------------
void DeleteItem::execute(Args& args)
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
    Aws::DynamoDB::Model::DeleteItemRequest req;

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

    const Aws::DynamoDB::Model::DeleteItemOutcome& result = dynamoClient.DeleteItem(req);
    if (result.IsSuccess())
    {}
    else
    {
        std::cout << "Failed to delete item:" << result.GetError() << std::endl;
    }
};

} /* dynamo namespace */

} /* app namespace */
