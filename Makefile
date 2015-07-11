CFLAGS=-Wall -g -Istb

check-syntax:
	clang -o /dev/null $(CFLAGS) -S ${CHK_SOURCES}
