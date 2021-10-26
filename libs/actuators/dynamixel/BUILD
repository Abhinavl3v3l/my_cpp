load("//bzl:genesis.bzl", "genesis_component")

genesis_component(
    name = "dynamixel",
    filename = "Dynamixel",
    deps = [
        ":registers",
        "//genesis/components/components/misc/bulk_operation_dxl:group_bulk_op"
        "@robotis//:dynamixel",
    ],
    visibility = ["//visibility:public"],
)

genesis_component(
    name = "registers",
    filename = "Registers",
    tags = ["nolint"],
    deps = [
        "@robotis//:dynamixel",
    ],
)
