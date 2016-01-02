all: hook.so testcp

hook.so: hook.cpp
	g++ -shared -fPIC hook.cpp -o hook.so -ldl

testcp: main.cpp
	g++ main.cpp -o testcp

run: testcp hook.so
	LD_PRELOAD=hook.so LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${PWD}" ./testcp
