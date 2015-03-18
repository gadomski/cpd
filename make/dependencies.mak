ARMADILLO_VERSION=4.650.3
GFLAGS_VERSION=2.1.1
CMAKE_COMMON_OPTIONS=-DCMAKE_BUILD_TYPE=Release -G Ninja


default:

install-build-system:
	sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
	sudo add-apt-repository -y ppa:smspillaz/cmake-2.8.12
	sudo apt-get update -qq
	sudo apt-get install -y \
		g++-4.8 \
		ninja-build \
		git \
		liblapack-dev \
		libarpack2-dev \
		libsuperlu3-dev \
		gfortran \
		cmake \
		cmake-data

install-dependencies:
	wget https://downloads.sourceforge.net/project/arma/armadillo-$(ARMADILLO_VERSION).tar.gz --no-check-certificate
	tar xzf armadillo-$(ARMADILLO_VERSION).tar.gz
	mkdir armadillo-$(ARMADILLO_VERSION)/build
	cd armadillo-$(ARMADILLO_VERSION)/build && \
		cmake .. $(CMAKE_COMMON_OPTIONS) && \
		ninja && \
		sudo ninja install
	git clone http://github.com/gadomski/fgt
	mkdir fgt/build
	cd fgt/build && \
		cmake .. $(CMAKE_COMMON_OPTIONS) -DARMA_64BIT_WORD=$(ARMA_64BIT_WORD) && \
		ninja && \
		sudo ninja install
	wget https://github.com/schuhschuh/gflags/archive/v$(GFLAGS_VERSION).tar.gz
	tar xzvf v$(GFLAGS_VERSION).tar.gz
	mkdir gflags-$(GFLAGS_VERSION)/build
	cd gflags-$(GFLAGS_VERSION)/build && \
		cmake .. $(CMAKE_COMMON_OPTIONS) && \
		ninja && \
		sudo ninja install

.PHONY: default install-build-system install-dependencies
