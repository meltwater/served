licenses(["notice"])

boost_path = "upstream"

load("/third_party/boost/tool", "boost_library")

boost_library(
  name = "assert",
)

boost_library(
  name = "config",
)

boost_library(
  name = "core",
)

boost_library(
  name = "predef",
)

boost_library(
  name = "system",
  srcs = glob([
    boost_path + "/system/src/*.cpp",
  ]),
  deps = [
    ":assert",
    ":config",
    ":core",
    ":predef",
  ],
)

boost_library(
  name = "throw_exception",
)

boost_library(
  name = "detail",
)

boost_library(
  name = "functional",
  deps = [
    ":detail",
  ],
)

boost_library(
  name = "io",
)

boost_library(
  name = "static_assert",
)

boost_library(
  name = "iterator",
  deps = [
    ":detail",
    ":static_assert",
  ],
)

boost_library(
  name = "concept_check",
)

boost_library(
  name = "optional",
)

boost_library(
  name = "range",
  deps = [
    ":concept_check",
    ":optional",
  ]
)

boost_library(
  name = "align",
)

boost_library(
  name = "utility",
)

boost_library(
  name = "smart_ptr",
  deps = [
    ":align",
    ":core",
    ":predef",
    ":throw_exception",
    ":utility",
  ],
)

boost_library(
  name = "preprocessor",
)

boost_library(
  name = "move",
)

boost_library(
  name = "mpl",
  deps = [
    ":preprocessor",
    ":move",
  ]
)

boost_library(
  name = "type_traits",
  deps = [
    ":core",
    ":mpl",
    ":static_assert",
  ]
)

boost_library(
  name = "bind",
)

boost_library(
  name = "function",
)

boost_library(
  name = "algorithm",
  deps = [
    ":function",
    ":range",
  ]
)

boost_library(
  name = "numeric_conversion",
)

boost_library(
  name = "array",
)

boost_library(
  name = "container",
)

boost_library(
  name = "math",
)

boost_library(
  name = "lexical_cast",
  deps = [
    ":numeric_conversion",
    ":container",
    ":array",
    ":math",
  ]
)

boost_library(
  name = "tokenizer",
)

boost_library(
  name = "date_time",
  deps = [
    ":smart_ptr",
    ":static_assert",
    ":mpl",
    ":type_traits",
    ":tokenizer",
    ":bind",
	":algorithm",
    ":iterator",
    ":lexical_cast",
    ":io",
  ],
)

boost_library(
  name = "filesystem",
  srcs = glob([
    boost_path + "/filesystem/src/*.cpp",
  ]),
  deps = [
    ":config",
    ":functional",
    ":io",
    ":iterator",
    ":range",
    ":smart_ptr",
    ":system",
    ":type_traits",
  ],
)

boost_library(
  name = "integer",
)

boost_library(
  name = "regex",
  defines = [
    "BOOST_FALLTHROUGH"
  ],
  srcs = glob([
    boost_path + "/regex/src/*.cpp",
    boost_path + "/regex/src/*.hpp",
  ]),
  deps = [
    ":assert",
    ":config",
    ":functional",
    ":integer",
    ":mpl",
    ":smart_ptr",
    ":throw_exception",
    ":type_traits",
  ]
)

boost_library(
  name = "asio",
  deps = [
    ":throw_exception",
    ":system",
    ":regex",
  ]
)

