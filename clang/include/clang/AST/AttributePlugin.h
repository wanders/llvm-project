//===--- AttributePlugin.h - RTTI for Attr class hierarchy ------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// Functionality for adding custom attributes into the Attr class hierarchy 
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_AST_ATTRIBUTEPLUGIN_H
#define LLVM_CLANG_AST_ATTRIBUTEPLUGIN_H

#include <llvm/Support/ExtensibleRTTI.h>

#include <clang/AST/Attr.h>

namespace clang {

template <class ThisT, class ParentT=InternalPluginBaseAttr>
class PluginAttribute : public llvm::RTTIExtends<ThisT, ParentT> {
public:
  using llvm::RTTIExtends<ThisT, ParentT>::RTTIExtends;
  static bool classof(const Attr *A) {
    if (A->getKind() != attr::InternalPluginBase)
      return false;
    const InternalPluginBaseAttr *R = static_cast<const InternalPluginBaseAttr *>(A);
    return R->isA(&ThisT::ID);
  }

  template <class... Args>
  static ThisT *Create(ASTContext &Ctx, const AttributeCommonInfo &CommonInfo, Args&&... args) {
    auto *A = new (Ctx) ThisT(Ctx, CommonInfo, std::forward<Args>(args)...);
    if (!A->isAttributeSpellingListCalculated() && !A->getAttrName())
      A->setAttributeSpellingListIndex(0);
    return A;
  }
};

}

#endif
