load("@rules_cc//cc:defs.bzl",  "cc_library")


cc_library(
    name = "hello",
    srcs = ["helloworld.cpp"],
    hdrs = ["helloworld.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "enum_test",
    srcs = ["enum_test.cpp"],
    hdrs = ["enum_test.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "maestro",
    srcs = ["MaestroDevice.cpp"],
    hdrs = ["MaestroDevice.hpp","DeviceOptions.hpp"],
    visibility = ["//visibility:public"],
)