hello:foo.h foo.c hello.c
	gcc foo.c hello.c -I. -o test_hello.exe