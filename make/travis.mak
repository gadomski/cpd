default:

build-and-test:
	mkdir build
	cd build && cmake .. \
		-DBUILD_TESTS=ON \
		-DCMAKE_BUILD_TYPE=Debug \
		-DBUILD_CLI=ON \
		-DARMA_64BIT_WORD=$(ARMA_64BIT_WORD) \
		-DBUILD_COVERAGE=$(CPD_BUILD_COVERAGE)
	make -C build
	build/bin/cpd-test
	sudo make -C build install
	/usr/local/bin/cpd

coverage:
	sudo pip install cpp-coveralls;
	coveralls \
		--gcov-options '\-lp' \
		-b build/ \
		--gcov /usr/bin/gcov-4.8 \
		--exclude build/vendor/ \
		--exclude build/test/ \
		--exclude armadillo-4.500.1/ \
		--exclude test/ \
		--exclude build/CMakeFiles


.PHONY: default build-and-test coverage
