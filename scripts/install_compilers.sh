sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
sudo apt-get update -qq

# Even if we're building clang, install g++-4.8 for updated libstdc++
sudo apt-get install g++-4.8
