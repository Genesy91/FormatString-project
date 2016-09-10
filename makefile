library: libformatfilter.c
	gcc -fPIC -Wall -shared  -o libformatfilter.so libformatfilter.c -ldl

tester: tester.o libformatfilter.so
	gcc -g -o tester tester.o -ldl

tester.o: tester.c
	gcc -Wall -g -c tester.c
