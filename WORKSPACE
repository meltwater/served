workspace(name = "com_github_meltwater_served")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "552baa34c17984ca873cd0c4fdd010c177737b6f",
    remote = "https://github.com/nelhage/rules_boost",
)
load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()
