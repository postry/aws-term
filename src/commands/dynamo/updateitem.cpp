/*
 * updateitem.cpp
 *
 *  Created on: Dec. 27, 2019
 *      Author: elagon
 */

#include "commands/dynamo/updateitem.hpp"
#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/UpdateItemRequest.h>
#include <aws/dynamodb/model/UpdateItemResult.h>
#include <iostream>

namespace app
{

namespace dynamo
{

//------------------------------------------------------------------------------
void UpdateItem::execute(Args& args)
{
    const Aws::String region("ca-central-1");
    Aws::String table;
    Aws::String partitionKeyName;
    Aws::String partitionKeyValue;
    Aws::String sortKeyName;
    Aws::String sortKeyValue;
    Aws::String attributeKeyName;
    Aws::String attributeKeyValue;

    Aws::String projection;
    args >> table >> partitionKeyName >> partitionKeyValue >> sortKeyName
            >> sortKeyValue >> attributeKeyName >> attributeKeyValue;
    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = region;
    Aws::DynamoDB::DynamoDBClient dynamoClient(clientConfig);
    Aws::DynamoDB::Model::UpdateItemRequest req;

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

    // Construct the SET update expression argument
    Aws::String update_expression("SET #a = :valueA");
    req.SetUpdateExpression(update_expression);
    // Construct attribute name argument
    // Note: Setting the ExpressionAttributeNames argument is required only
    // when the name is a reserved word, such as "default". Otherwise, the
    // name can be included in the update_expression, as in
    // "SET MyAttributeName = :valueA"
    Aws::Map<Aws::String, Aws::String> expressionAttributeNames;
    expressionAttributeNames["#a"] = attributeKeyName;
    req.SetExpressionAttributeNames(expressionAttributeNames);

    // Construct attribute value argument
    Aws::DynamoDB::Model::AttributeValue attributeUpdatedValue;
    attributeUpdatedValue.SetS(attributeKeyValue);
    Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue> expressionAttributeValues;
    expressionAttributeValues[":valueA"] = attributeUpdatedValue;
    req.SetExpressionAttributeValues(expressionAttributeValues);
    // Update the item
    const Aws::DynamoDB::Model::UpdateItemOutcome &result =
            dynamoClient.UpdateItem(req);
    if (!result.IsSuccess())
    {
        std::cout << result.GetError().GetMessage() << std::endl;
    }
    else
    {
        std::cout << "Item was updated" << std::endl;
    }
};


} /* dynamo namespace */

} /* app namespace */
