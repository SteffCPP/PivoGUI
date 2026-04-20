# ==========================================
#   THIS FILE IS FOR TESTING PURPOSES ONLY
# ==========================================

all: main

main:
	g++ test/main.cpp -Iinc -Llib -lEGUI -Wl,-rpath=lib -o test/bin/main.exe -std=c++23

pong:
	g++ test/pong.cpp -Iinc -Llib -lEGUI -Wl,-rpath=lib -o test/bin/pong.exe -std=c++23

runMain: 
	test/bin/main
runPong:
	test/bin/pong