ARMADILLO_VERSION=4.600.4
CMAKE_COMMON_OPTIONS=-DCMAKE_BUILD_TYPE=Release


default:

install-travis:
	sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
	sudo add-apt-repository ppa:smspillaz/cmake-2.8.12 -y
	sudo apt-get update -qq
	sudo apt-get install -y g++-4.8 cmake cmake-data libarmadillo-dev
	wget https://downloads.sourceforge.net/project/arma/armadillo-$(ARMADILLO_VERSION).tar.gz --no-check-certificate
	tar xzf armadillo-$(ARMADILLO_VERSION).tar.gz
	mkdir armadillo-$(ARMADILLO_VERSION)/build
	cd armadillo-$(ARMADILLO_VERSION)/build; \
		cmake .. $(CMAKE_COMMON_OPTIONS); \
		make; \
		sudo make install


.PHONY: default install-travis
