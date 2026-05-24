#include "commands.hpp"

#include <iostream>
#include <stdexcept>

void vasilenko::processPrint(const std::string& name, const vasilenko::DictMap& dicts)
{
  auto it = dicts.find(name);
  if (it == dicts.end()) {
    std::cout << "<EMPTY>\n";
    return;
  }
  auto dictIt = it->second.begin();
  if (dictIt == it->second.end()) {
    std::cout << "<EMPTY>\n";
    return;
  }
  std::cout << name;
  for (; dictIt != it->second.end(); ++dictIt) {
    std::cout << " " << dictIt->first << " " << dictIt->second;
  }
  std::cout << '\n';
}

void vasilenko::processUnion(const std::string& target, const std::string& left, const std::string& right, vasilenko::DictMap& dicts)
{
  vasilenko::Dictionary newDict;
  if (dicts.count(left) > 0) {
    for (auto it = dicts.at(left).begin(); it != dicts.at(left).end(); ++it) {
      newDict.push(it->first, it->second);
    }
  }
  if (dicts.count(right) > 0) {
    for (auto it = dicts.at(right).begin(); it != dicts.at(right).end(); ++it) {
      try {
        newDict.get(it->first);
      } catch (const std::out_of_range&) {
        newDict.push(it->first, it->second);
      }
    }
  }
  dicts[target] = std::move(newDict);
}

void vasilenko::processIntersect(const std::string& target, const std::string& left, const std::string& right, vasilenko::DictMap& dicts)
{
  vasilenko::Dictionary newDict;
  if (dicts.count(left) > 0 && dicts.count(right) > 0) {
    for (auto it = dicts.at(left).begin(); it != dicts.at(left).end(); ++it) {
      try {
        dicts.at(right).get(it->first);
        newDict.push(it->first, it->second);
      } catch (const std::out_of_range&) {
      }
    }
  }
  dicts[target] = std::move(newDict);
}

void vasilenko::processComplement(const std::string& target, const std::string& left, const std::string& right, vasilenko::DictMap& dicts)
{
  vasilenko::Dictionary newDict;
  if (dicts.count(left) > 0) {
    for (auto it = dicts.at(left).begin(); it != dicts.at(left).end(); ++it) {
      if (dicts.count(right) == 0) {
        newDict.push(it->first, it->second);
        continue;
      }
      try {
        dicts.at(right).get(it->first);
      } catch (const std::out_of_range&) {
        newDict.push(it->first, it->second);
      }
    }
  }
  dicts[target] = std::move(newDict);
}
