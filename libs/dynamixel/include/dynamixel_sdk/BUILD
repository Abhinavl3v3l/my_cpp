# load("//bzl:module.bzl","cc_import","cc_library")

# cc_import(
#   name = "dynamixel_import",
#   static_library = "c++/include/dynamixel_sdk/dynamixel_sdk.lib",
#   hdrs = glob(["c++/include/dynamixel_sdk/*.h"]),
#   visibility = ["//visibility:public"],
# )

# export_files(glob(["*.h"]))

cc_library(
    name = "dynamixel_lib",
    hdrs = glob(["*.h"]),
	strip_include_prefix = ".",
    deps = [],
	visibility = ["//visibility:public"],
)

