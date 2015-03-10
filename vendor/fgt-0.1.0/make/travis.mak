build:
	mkdir build; cd build; \
	    cmake .. -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release; \
	    make

test:
	build/bin/fgt-test
	build/bin/fgt-trial

install:
	cd build; sudo make install


.PHONY: build test install
