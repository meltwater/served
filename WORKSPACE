workspace(name = "com_github_meltwater_served")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "72ec09168e5c3a296f667b3d956a853ccd65c8ed",
    remote = "https://github.com/nelhage/rules_boost",
)
load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()
