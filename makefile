.PHONY: clean all test  
all: bin/Python-Snake
  
bin/Python-Snake: build/Main.o build/Menu.o build/Snake.o
	g++ -std=c++11 -Wall -Werror build/src/Main.o build/src/Menu.o build/src/Snake.o -o bin/Python-Snake -lsfml-graphics -lsfml-window -lsfml-system

build/Main.o: src/Main.cpp
	g++ -std=c++11 -Wall -Werror -c src/Main.cpp -o build/src/Main.o 

build/Snake.o: src/Snake.cpp
	g++ -std=c++11 -Wall -Werror -c src/Snake.cpp -o build/src/Snake.o 

build/Menu.o: src/Menu.cpp
	g++ -std=c++11 -Wall -Werror -c src/Menu.cpp -o build/src/Menu.o 

clean:
	rm -rf build/src/*.o build/test/*.o bin/Python-Snake bin/Test \
			$(GTEST_LIB_DIR)/lib/libgtest.a $(GTEST_LIB_DIR)/lib/libgtest_main.a $(GTEST_LIB_DIR)/lib/*.o

GTEST_LIB_DIR = thirdparty/googletest

USER_DIR = src

USER_DIR_O = build/test

USER_DIR_b = bin

CPPFLAGS += -isystem thirdparty/googletest/include

CXXFLAGS += -g -Wall -Wextra -pthread -std=c++11

GTEST_LIBS = libgtest.a libgtest_main.a

TESTS = unittest.cpp

GTEST_HEADERS = $(GTEST_LIB_DIR)/include/gtest/*.h \
                $(GTEST_LIB_DIR)/include/gtest/internal/*.h

GTEST_SRCS_ = $(GTEST_LIB_DIR)/src/*.cc $(GTEST_LIB_DIR)/src/*.h $(GTEST_HEADERS)

$(GTEST_LIB_DIR)/lib/gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_LIB_DIR) $(CXXFLAGS) -c \
            $(GTEST_LIB_DIR)/src/gtest-all.cc -o $(GTEST_LIB_DIR)/lib/gtest-all.o

$(GTEST_LIB_DIR)/lib/gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_LIB_DIR) $(CXXFLAGS) -c \
            $(GTEST_LIB_DIR)/src/gtest_main.cc -o $(GTEST_LIB_DIR)/lib/gtest_main.o

$(GTEST_LIB_DIR)/lib/libgtest.a : $(GTEST_LIB_DIR)/lib/gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

$(GTEST_LIB_DIR)/lib/libgtest_main.a : $(GTEST_LIB_DIR)/lib/gtest-all.o $(GTEST_LIB_DIR)/lib/gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

test: $(GTEST_LIB_DIR)/lib/libgtest_main.a $(GTEST_LIB_DIR)/lib/libgtest.a $(TESTS)

$(TESTS) : $(USER_DIR_O)/Snake.o $(USER_DIR_O)/unittest.o $(USER_DIR_O)/Menu.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -L$(GTEST_LIB_DIR)/lib -lgtest_main -lpthread $^ -o $(USER_DIR_b)/Test -lsfml-graphics -lsfml-window -lsfml-system

$(USER_DIR_O)/unittest.o : test/unittest.cpp \
                     $(USER_DIR)/Snake.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c test/unittest.cpp -o $@

$(USER_DIR_O)/Snake.o : $(USER_DIR)/Snake.cpp $(USER_DIR)/Snake.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Snake.cpp -o $@

$(USER_DIR_O)/Menu.o : $(USER_DIR)/Menu.cpp $(USER_DIR)/Menu.hpp $(GTEST_HEADERS)

	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Menu.cpp -o $@
