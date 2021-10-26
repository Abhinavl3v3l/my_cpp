load("//bzl:genesis.bzl", "genesis_component")

genesis_component(
    name = "maestro",
    filename = "Maestro",
    deps = [
        ":config",
        "@com_nvidia_isaac_engine//engine/core/math",
    ],
    alwayslink = False,
    visibility = ["//visibility:public"],
)

cc_library(
    name = "config",
    srcs = [
    ],
    hdrs = [
        "MaestroConfig.hpp",
    ],
    deps = [
        "@com_nvidia_isaac_engine//engine/core/math",
    ],
    visibility = ["//visibility:public"],
)
