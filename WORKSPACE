workspace(name = "com_github_datasift_served")

git_repository(
    name = "com_github_nelhage_boost",
    remote = "https://github.com/nelhage/rules_boost.git",
    commit = "ead0110ff90d5d90d2eb67e7e78f34f42d8486a1",
)

load("@com_github_nelhage_boost//:boost/boost.bzl", "boost_deps")
boost_deps()

git_repository(
    name = "com_googlesource_code_re2",
    remote = "https://github.com/google/re2.git",
    commit = "22fc950c75d238f8b2dcbc43d8a60573cad2b8d7",
)
