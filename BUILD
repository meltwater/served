licenses(["notice"])

exports_files(["LICENSE.md"])

cc_library(
    name = "served",
    copts = [
        "-Iexternal/com_googlesource_code_re2",
    ],
    srcs = glob(
        [
            "src/served/*.cpp",
            "src/served/mux/*.cpp",
            "src/served/net/*.cpp",
        ],
        exclude = [
            "src/served/*.test.cpp",
            "src/served/mux/*.test.cpp",
            "src/served/net/*.test.cpp",
        ],
    ),
    hdrs = glob(
        [
            "src/served/*.hpp",
            "src/served/mux/*.hpp",
            "src/served/net/*.hpp",
        ],
        exclude = [
            "src/served/version.hpp"
        ],
    ) + [":servedversion"],
    strip_include_prefix = "src/",
    visibility = ["//visibility:public"],
    deps = [
        "@boost//:system",
        "@boost//:asio",
        "@com_googlesource_code_re2//:re2",
    ],
)

cc_test(
    name = "served-test",
    copts = [
        "-Iexternal/com_googlesource_code_re2",
        "-Isrc",
    ],
    srcs = glob(
        [
            "src/served/*.test.cpp",
            "src/served/mux/*.test.cpp",
            "src/served/net/*.test.cpp",
            "src/test/catch.cpp",
            "src/test/catch.hpp",
        ],
    ),
    tags = [ "large" ],
    timeout = "short",
    deps = [ "//:served" ],
)

genrule(
    name = "servedversion",
    srcs = [],
    outs = ["src/served/version.hpp"],
    cmd = """
echo '#ifndef SERVED_VERSION_HPP_INCLUDED' > $@
echo '#define SERVED_VERSION_HPP_INCLUDED' >> $@
echo '#define APPLICATION_NAME \"Served HTTP REST Library\"' >> $@
echo '#define APPLICATION_CODENAME \"served\"' >> $@
echo '#define APPLICATION_COPYRIGHT_YEARS \"2014\"' >> $@
echo '#define APPLICATION_VERSION_STRING \"1.4.3-DS1\"' >> $@
echo '#define APPLICATION_VENDOR_ID \"com.datasift\"' >> $@
echo '#define APPLICATION_VENDOR_NAME \"DataSift\"' >> $@
echo '#define APPLICATION_VENDOR_URL \"datasift.com\"' >> $@
echo '#define APPLICATION_ID = \"com.datasift.served\"' >> $@
echo '#endif' >> $@
  """,
)
