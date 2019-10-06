#include "catch.hpp"

#include <sstream>
#include <iostream>
#include "FP/hello.h"

TEST_CASE( "hello() says hello" ) {
    std::ostringstream out;
	std::streambuf* coutbuf = std::cout.rdbuf();

    std::cout << "Running testcase hello()\n" << std::endl;

    std::cout.rdbuf(out.rdbuf()); //redirect cout to out
    hello("tester");
	hello("you");
    std::cout.rdbuf(coutbuf);

	REQUIRE( out.str() == "Hello, tester!\nHello, you!\n");
}

TEST_CASE( "hello() says otherwise" ) {
    std::ostringstream out;
	std::streambuf* coutbuf = std::cout.rdbuf();

    std::cout << "Running testcase otherwise()\n" << std::endl;

    std::cout.rdbuf(out.rdbuf()); //redirect cout to out
    hello("new test");
	hello("us");
    std::cout.rdbuf(coutbuf);

	REQUIRE( out.str() == "Hello, new test!\nHello, us!\n");
}
