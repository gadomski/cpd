ARMADILLO_VERSION=4.600.4
GFLAGS_VERSION=2.1.1
CMAKE_COMMON_OPTIONS=-DCMAKE_BUILD_TYPE=Release -G Ninja


default:

install-on-ubuntu-trusty: \
	install-build-system-apt-trusty \
	install-dependencies-apt-general

install-on-ubuntu-precise: \
	install-build-system-apt-precise \
	install-dependencies-apt-general

install-dependencies-apt-general: \
	install-armadillo-dependencies-apt \
	install-armadillo-src \
	install-gflags-src

install-on-osx: install-build-system-homebrew
	brew install armadillo
	brew install gflags

install-build-system-apt-trusty:
	sudo apt-get update -qq
	sudo apt-get install -y build-essential cmake ninja-build git

install-build-system-apt-precise:
	sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
	sudo add-apt-repository ppa:smspillaz/cmake-2.8.12 -y
	sudo apt-get update -qq
	sudo apt-get install -y g++-4.8 cmake cmake-data ninja-build git

install-build-system-homebrew:
	brew update
	brew install cmake
	brew install ninja

install-armadillo-dependencies-apt:
	sudo apt-get -y install \
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
	install-on-ubuntu-trusty \
	install-on-ubuntu-precise \
	install-dependencies-apt-general \
	install-on-osx \
	install-build-system-apt-trusty \
	install-build-system-apt-precise \
	install-build-system-homebrew \
	install-armadillo-dependencies-apt \
	install-armadillo-src \
	install-gflags-src
