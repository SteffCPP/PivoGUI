# ==========================================
#   THIS FILE IS FOR TESTING PURPOSES ONLY
# ==========================================

all: shapes

compile_shapes:
	g++ test/shapes.cpp -Iinc -g -Llib -lPIVO -Wl,-rpath=lib -o test/bin/shapes -std=c++23

compile_pong:
	g++ test/pong.cpp -Iinc -g -Llib -lPIVO -Wl,-rpath=lib -o test/bin/pong -std=c++23

shapes: compile_shapes
	test/bin/shapes
pong: compile_pong
	test/bin/pong