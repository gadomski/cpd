coveralls \
    --gcov-options '\-lp' \
    -b build/ \
    --gcov /usr/bin/gcov-4.8 \
    --exclude build/vendor/ \
    --exclude build/test/ \
    --exclude armadillo-4.500.1/ \
    --exclude test/ \
    --exclude build/CMakeFiles
