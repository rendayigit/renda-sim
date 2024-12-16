#include "json/json.hpp"
#include <string>

Json::Json(const std::string &jsonFile) : m_jsonFile(jsonFile) {
  try {
    // Read the json file and store the root node in `m_root`
    pt::read_json(jsonFile, m_root);
  } catch (std::exception const &e) {
    throw std::runtime_error("Cannot read " + jsonFile + " : " + e.what());
  }
}

Json Json::getNode(const std::string &key) {
  // Push the provided key to the key history
  m_keyHistory.push_back(key);

  return Json(m_jsonFile, m_root.get_child(key), m_keyHistory);
}

std::string Json::getKey() { return m_keyHistory.back(); }

std::vector<std::string> Json::getNodePath() { return m_keyHistory; }

Json Json::at(int index) {
  if (getSize() == 0) {
    throw std::invalid_argument("Json node is not an array.");
  }

  if ((getSize() <= index) or (getSize() + 1 <= abs(index))) {
    throw std::out_of_range("Index out of range.");
  }

  auto currentIndex = m_root.begin();

  if (index >= 0) {
    std::advance(currentIndex, index);
  } else {
    std::advance(currentIndex, getSize() + index);
  }

  m_keyHistory.push_back(currentIndex->first);

  return Json(m_jsonFile, currentIndex->second, m_keyHistory);
}

int Json::getSize() { return static_cast<int>(m_root.size()); }

template <typename t> void Json::setValue(t value) {
  // Read the json file and store the root node in `m_root`
  pt::read_json(m_jsonFile, m_root);

  // The path of the node to be written
  std::string nodePath;

  // Construct the path to the node to be written
  for (auto &key : m_keyHistory) {
    nodePath += key + '.';
  }

  // Erase the last '.' to fix the path
  nodePath.erase(nodePath.length() - 1); // Erase last '.'

  // Write the value to the node
  m_root.put<t>(nodePath, value);

  // Overwrite the json file with the new value
  pt::write_json(m_jsonFile, m_root);
}

Json::Json(std::string &jsonFile, const pt::ptree &root, std::vector<std::string> keyHistory)
    : m_jsonFile(jsonFile), m_root(root), m_keyHistory(std::move(keyHistory)){};

template void Json::setValue(bool);
template void Json::setValue(float);
template void Json::setValue(double);
template void Json::setValue(long double);
template void Json::setValue(char);
template void Json::setValue(std::string);
template void Json::setValue(signed char);
template void Json::setValue(unsigned char);
template void Json::setValue(short int);
template void Json::setValue(unsigned short int);
template void Json::setValue(int);
template void Json::setValue(unsigned int);
template void Json::setValue(long int);
template void Json::setValue(unsigned long int);
template void Json::setValue(long long int);
template void Json::setValue(unsigned long long int);