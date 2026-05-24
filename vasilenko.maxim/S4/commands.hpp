#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <map>
#include <string>

#include "BSTree.hpp"

namespace vasilenko {

using Dictionary = BSTree<int, std::string>;
using DictMap = std::map<std::string, Dictionary>;

void processPrint(const std::string& name, const DictMap& dicts);
void processUnion(const std::string& target, const std::string& left, const std::string& right, DictMap& dicts);
void processIntersect(const std::string& target, const std::string& left, const std::string& right, DictMap& dicts);
void processComplement(const std::string& target, const std::string& left, const std::string& right, DictMap& dicts);

}

#endif
