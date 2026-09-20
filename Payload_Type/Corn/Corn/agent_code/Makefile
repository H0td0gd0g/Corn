CXX     := x86_64-w64-mingw32-gcc
BUILD   := ./build
INCLUDE := -I include
SRC     := source/*.c main.c

CFLAGS  := -lwinhttp -lws2_32

all: exe

exe:
	mkdir -p $(BUILD)
	$(CXX) $(INCLUDE) $(SRC) $(CFLAGS) -o $(BUILD)/corn.exe

clean:
	rm -rf $(BUILD)