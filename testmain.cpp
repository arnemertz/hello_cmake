#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <sstream>
#include <iostream>
#include "hello.h"

TEST_CASE( "hello() says hello" ) {
    std::ostringstream out;
	std::streambuf* coutbuf = std::cout.rdbuf();
	
    std::cout.rdbuf(out.rdbuf()); //redirect cout to out
    hello("tester");
	hello("you");
    std::cout.rdbuf(coutbuf);

	REQUIRE( out.str() == "Hello, tester!\nHello, you!\n");
}