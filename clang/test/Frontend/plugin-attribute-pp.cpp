// RUN: split-file %s %t
// RUN: %clang -fplugin=%llvmshlibdir/Attribute%pluginext -E %t/has_attr.cpp | FileCheck %t/has_attr.cpp
// RUN: %clang -fplugin=%llvmshlibdir/Attribute%pluginext -E %t/has_attr.c | FileCheck %t/has_attr.c
// REQUIRES: plugins, examples


//--- has_attr.cpp
#if __has_attribute (example)
// CHECK: YES - It did exist
YES - It did exist
#endif
#if __has_cpp_attribute (example)
// CHECK: YES - It did cpp-exist
YES - It did cpp-exist
#endif

#if __has_attribute (doesnt_exist)
// CHECK-NOT: NO - There is no such attribute
NO - There is no such attribute
#endif


//--- has_attr.c
#if __has_attribute (example)
// CHECK: YES - It did exist
YES - It did exist
#endif
#if __has_c_attribute (example)
// CHECK: YES - It did c-exist
YES - It did c-exist
#endif

#if __has_attribute (doesnt_exist)
// CHECK-NOT: NO - There is no such attribute
NO - There is no such attribute
#endif
