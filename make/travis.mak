default:

build-and-test:
	mkdir build
	cd build && cmake .. \
		-DBUILD_TESTS=ON \
		-DCMAKE_BUILD_TYPE=Debug \
		-DBUILD_CLI=ON \
		-DARMA_64BIT_WORD=$(ARMA_64BIT_WORD)
	make -C build
	build/bin/cpd-test
	sudo make -C build install
	/usr/local/bin/cpd

.PHONY: default build-and-test coverage
