#include "json/json.hpp"
#include "common.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

std::string testJsonFilePath = getExecutableDirectory() + "../tests/test.json";

TEST(Json, GetValue) {
  // Get node "first_name"
  auto firstNameValue = Json(testJsonFilePath).getNode("first_name").getValue<std::string>();

  // Test if "first_name" node value is "John"
  EXPECT_EQ(firstNameValue, "John");

  // Get node "address.state"
  auto stateValue = Json(testJsonFilePath).getNode("address").getNode("state").getValue<std::string>();

  // Test if "address.state" node value is "NY"
  EXPECT_EQ(stateValue, "NY");
}

TEST(Json, SetValue) {
  // Get "is_alive" node value
  auto isAliveValue = Json(testJsonFilePath).getNode("is_alive").getValue<bool>();

  // Invert the "is_alive" node value and write it to test.json
  Json(testJsonFilePath).getNode("is_alive").setValue<bool>(not isAliveValue);

  // Get "is_alive" node value again
  auto modifiedIsAliveValue = Json(testJsonFilePath).getNode("is_alive").getValue<bool>();

  // Test if "is_alive" is modified
  EXPECT_EQ(modifiedIsAliveValue, not isAliveValue);

  // Revert test.json back to original state
  Json(testJsonFilePath).getNode("is_alive").setValue<bool>(isAliveValue);
}

TEST(Json, JsonArray) {
  // Get size of "phone_numbers"
  auto size = Json(testJsonFilePath).getNode("phone_numbers").getSize();

  // Test if "phone_numbers" size is 2
  EXPECT_EQ(size, 2);

  // Iterate through "phone_numbers"
  for (int i = 0; i < size; i++) {
    auto item = Json(testJsonFilePath).getNode("phone_numbers").at(i);

    switch (i) {
    case 0:
      // Test if "phone_numbers[0]" has the correct values
      EXPECT_EQ(item.getNode("number").getValue<std::string>(), "212 555-1234");
      EXPECT_EQ(item.getNode("type").getValue<std::string>(), "home");
      break;
    case 1:
      // Test if "phone_numbers[1]" has the correct values
      EXPECT_EQ(item.getNode("number").getValue<std::string>(), "646 555-4567");
      EXPECT_EQ(item.getNode("type").getValue<std::string>(), "office");
      break;
    default:
      break;
    }
  }

  // Get size of "children"
  size = Json(testJsonFilePath).getNode("children").getSize();

  // Test if "children" size is 3
  EXPECT_EQ(size, 3);

  // Test if the child has the correct value
  auto child = Json(testJsonFilePath).getNode("children").at(0);
  EXPECT_EQ(child.getValue<std::string>(), "Catherine");

  // Test if the child has the correct value
  child = Json(testJsonFilePath).getNode("children").at(1);
  EXPECT_EQ(child.getValue<std::string>(), "Thomas");

  // Test if the child has the correct value
  child = Json(testJsonFilePath).getNode("children").at(2);
  EXPECT_EQ(child.getValue<std::string>(), "Trevor");

  // Test if the child has the correct value with negative index
  child = Json(testJsonFilePath).getNode("children").at(-1);
  EXPECT_EQ(child.getValue<std::string>(), "Trevor");

  // Test if the child has the correct value with negative index
  child = Json(testJsonFilePath).getNode("children").at(-2);
  EXPECT_EQ(child.getValue<std::string>(), "Thomas");

  // Test if the child has the correct value with negative index
  child = Json(testJsonFilePath).getNode("children").at(-3);
  EXPECT_EQ(child.getValue<std::string>(), "Catherine");
}

TEST(Json, JsonKey) {
  // Get address node
  auto address = Json(testJsonFilePath).getNode("address");

  // Test if address node key is "address"
  EXPECT_EQ(address.getKey(), "address");

  // Get city node using index
  auto city = address.at(1);

  // Test if city node value key is "city"
  EXPECT_EQ(city.getKey(), "city");

  // Get children
  auto children = Json(testJsonFilePath).getNode("children");

  // Get child at index 2
  auto child = children.at(2);

  // Test if json object with no key returns empty
  EXPECT_TRUE(child.getKey().empty());

  // Get Phone number at index 1
  auto phoneNumber = Json(testJsonFilePath).getNode("phone_numbers").at(1).getNode("number");

  // Test if phone number key is "number"
  EXPECT_EQ(phoneNumber.getKey(), "number");
}

TEST(Json, JsoNodePath) {
  // Get street address node
  auto streetAddress = Json(testJsonFilePath).getNode("address").getNode("street_address");

  // Test if node path is correct
  EXPECT_EQ(streetAddress.getNodePath().size(), 2);
  EXPECT_EQ(streetAddress.getNodePath().at(0), "address");
  EXPECT_EQ(streetAddress.getNodePath().at(1), "street_address");

  // Get number node using index
  auto number = Json(testJsonFilePath).getNode("phone_numbers").at(1).getNode("number");

  // Test if node path is correct
  EXPECT_EQ(number.getNodePath().size(), 3);
  EXPECT_EQ(number.getNodePath().at(0), "phone_numbers");
  EXPECT_EQ(number.getNodePath().at(1), "");
  EXPECT_EQ(number.getNodePath().at(2), "number");

  // Get child at index 2
  auto child = Json(testJsonFilePath).getNode("children").at(2);

  // Test if node path is correct
  EXPECT_EQ(child.getNodePath().size(), 2);
  EXPECT_EQ(child.getNodePath().at(0), "children");
  EXPECT_EQ(child.getNodePath().at(1), "");
}

TEST(Json, FaultyUsage) {
  std::string invalid = "invalid";

  // Verify that an exception is thrown when trying to get a node from a non-existent json file
  EXPECT_THROW(Json(invalid).getNode(invalid).getValue<std::string>(), std::runtime_error);

  // Verify that an exception is thrown when trying to get a Json array node from a non array node
  EXPECT_THROW(Json(testJsonFilePath).getNode("age").at(3), std::invalid_argument);

  // Verify that an exception is thrown when trying to get a Json array node using an index that is out of bounds
  EXPECT_THROW(Json(testJsonFilePath).getNode("phone_numbers").at(3), std::out_of_range);

  // Verify that an exception is thrown when trying to get a Json array node using an index that is out of bounds
  EXPECT_THROW(Json(testJsonFilePath).getNode("children").at(3), std::out_of_range);

  // Verify that an exception is thrown when trying to get a Json array node using a negative index that is out of
  // bounds
  EXPECT_THROW(Json(testJsonFilePath).getNode("children").at(-4), std::out_of_range);
}