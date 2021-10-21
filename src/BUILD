load("@rules_cc//cc:defs.bzl", "cc_binary")


cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = ["//libs/nlohmann:nlohmann",
            "//libs/dynamixel/include/dynamixel_sdk:dynamixel_lib",
            "//libs/dynamixel/src/dynamixel_sdk:dynamixel_lib_cpp"
            ],
)