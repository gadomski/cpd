#!/bin/bash
# Push doxygen documentation to `gh-pages`.
# Expects to be run from the top level directory.
#
# Inspired by travis-doxygen.sh from miloyip/rapidjson

set -ex

skip() {
    echo "SKIPPING: $@" 1>&2
    echo "Exiting..."
    exit 0
}

abort() {
    echo "ERROR: $@" 1>&2
    echo "Exiting..."
    exit 1
}

[ -f scripts/gh-pages.sh ] || abort "scripts/gh-pages.sh must be run from PROJECT_SOURCE_DIR"

if [ "${TRAVIS}" = "true" ]; then
    [ "${TRAVIS_PULL_REQUEST}" = "false" ] || skip "Not building docs for pull requests"
    [ "${TRAVIS_BRANCH}" = "master" ] || skip "Only building docs for master branch"
    [ "${TRAVIS_JOB_NUMBER}" = "${TRAVIS_BUILD_NUMBER}.1" ] || skip "Only build docs once"

    git config --global user.name "Travis CI"
    git config --global user.email "travis@localhost"
fi

mkdir -p build/docs
cd build/docs
rm -rf html
git clone -b gh-pages https://github.com/gadomski/cpd html
cd html
rm -rf .git/index
git clean -df
cd ../..
make doc
cd docs/html
git add --all
git diff-index --quiet HEAD || git commit -m "scripts/gh-pages.sh"

if [ "${TRAVIS}" = "true" ]; then
    git push "https://${GH_TOKEN}@github.com/gadomski/cpd.git" gh-pages
else
    git push git@github.com:gadomski/cpd gh-pages
fi
