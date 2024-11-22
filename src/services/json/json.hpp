#pragma once

#include <boost/property_tree/json_parser.hpp>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace pt = boost::property_tree;

class Json {
public:
  /**
   * @brief Construct a new Json object
   *
   * @param jsonFile The path to the json file
   * @throws std::runtime_error If the json file cannot be read
   */
  explicit Json(const std::string &jsonFile);

  /**
   * @brief Get the given node from the json file using the given key
   *
   * @param key The key of the node
   * @return The the node
   */
  Json getNode(const std::string &key);

  /**
   * @brief Get the value of the given node
   *
   * @param t The type of the value
   * @return The value
   */
  template <typename t> t getValue() { return m_root.get_value<t>(); }

  /**
   * @brief Get the key of the node
   *
   * @return Key of the node
   */
  std::string getKey();

  /**
   * @brief Get the path of the node
   *
   * @return The path of the node
   */
  std::vector<std::string> getNodePath();

  /**
   * @brief Get the Json node at the given index
   *
   * @param index The index of the node. The index can be positive or negative. Negative index will start from the end
   * of the array.
   * @throws std::invalid_argument If the Json node is not an array
   * @throws std::out_of_range If the index is out of range
   * @return The Json node at the given index
   */
  Json at(int index);

  /**
   * @brief Get the size of the Json array
   *
   * @return The size of the Json array
   */
  int getSize();

  /**
   * @brief Set the value of the node
   *
   * @param value The value
   */
  template <typename t> void setValue(t value);

private:
  // Hidden constructor for `getNode()` recursive function
  explicit Json(std::string &jsonFile, const pt::ptree &root, std::vector<std::string> keyHistory);

  // The path to the json file
  std::string m_jsonFile;

  // The root of the json file
  pt::ptree m_root;

  // The history of the keys
  std::vector<std::string> m_keyHistory;
};