

#include "clang/Basic/ParsedAttrInfo.h"
#include "llvm/Support/ManagedStatic.h"
#include <list>
#include <memory>

using namespace clang;

LLVM_INSTANTIATE_REGISTRY(ParsedAttrInfoRegistry)

const std::list<std::unique_ptr<ParsedAttrInfo>> &
clang::getAttributePluginInstances(void)
{
  static llvm::ManagedStatic<std::list<std::unique_ptr<ParsedAttrInfo>>>
      PluginAttrInstances;
  if (PluginAttrInstances->empty())
    for (auto It : ParsedAttrInfoRegistry::entries())
      PluginAttrInstances->emplace_back(It.instantiate());

  return *PluginAttrInstances;
}
