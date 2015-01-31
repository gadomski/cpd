ARMADILLO_VERSION=4.600.4
GFLAGS_VERSION=2.1.1
CMAKE_COMMON_OPTIONS=-DCMAKE_BUILD_TYPE=Release -G Ninja


default:

install-on-ubuntu: \
	install-build-system-apt \
	install-armadillo-dependencies-apt \
	install-armadillo-src \
	install-figtree-git \
	install-gflags-src

install-on-osx: install-build-system-homebrew install-figtree-git
	brew install armadillo
	brew install gflags

install-build-system-apt:
	sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
	sudo add-apt-repository ppa:smspillaz/cmake-2.8.12 -y
	sudo apt-get update -qq
	sudo apt-get install g++-4.8 cmake cmake-data ninja-build

install-build-system-homebrew:
	brew update
	brew install cmake
	brew install ninja

install-armadillo-dependencies-apt:
	sudo apt-get install \
		liblapack-dev \
		libarpack2-dev \
		libsuperlu3-dev \
		gfortran

install-armadillo-src:
	wget https://downloads.sourceforge.net/project/arma/armadillo-$(ARMADILLO_VERSION).tar.gz --no-check-certificate
	tar xzf armadillo-$(ARMADILLO_VERSION).tar.gz
	mkdir armadillo-$(ARMADILLO_VERSION)/build
	cd armadillo-$(ARMADILLO_VERSION)/build && \
		cmake .. $(CMAKE_COMMON_OPTIONS) && \
		ninja && \
		sudo ninja install

install-figtree-git:
	git clone https://github.com/gadomski/figtree.git -b master
	mkdir figtree/build
	cd figtree/build && \
		cmake .. $(CMAKE_COMMON_OPTIONS) && \
		ninja && \
		sudo ninja install

install-gflags-src:
	wget https://github.com/schuhschuh/gflags/archive/v$(GFLAGS_VERSION).tar.gz
	tar xzvf v$(GFLAGS_VERSION).tar.gz
	mkdir gflags-$(GFLAGS_VERSION)/build
	cd gflags-$(GFLAGS_VERSION)/build && \
		cmake .. $(CMAKE_COMMON_OPTIONS) && \
		ninja && \
		sudo ninja install


.PHONY: \
	default \
	install-on-ubuntu \
	install-on-osx \
	install-build-system-apt \
	install-build-system-homebrew \
	install-armadillo-dependencies-apt \
	install-armadillo-src \
	install-figtree-git \
	install-gflags-src
