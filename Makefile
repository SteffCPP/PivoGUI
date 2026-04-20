# ==========================================
#   THIS FILE IS FOR TESTING PURPOSES ONLY
# ==========================================

all: main

compile_main:
	g++ test/main.cpp -Iinc -Llib -lEGUI -Wl,-rpath=lib -o test/bin/main -std=c++23

compile_pong:
	g++ test/pong.cpp -Iinc -Llib -lEGUI -Wl,-rpath=lib -o test/bin/pong -std=c++23

main: compile_main
	test/bin/main
pong: compile_pong
	test/bin/pong