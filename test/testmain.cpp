#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <sstream>
#include <iostream>
#include "hello.h"

class RedirectConsole
{

public:
    explicit RedirectConsole(std::ostream &ostream)
        : coutbuf{std::cout.rdbuf()}
    {
        std::cout.rdbuf(ostream.rdbuf()); //redirect cout to ostream
    }

    ~RedirectConsole()
    {
        std::cout.rdbuf(coutbuf);
    }

private:
    std::streambuf *coutbuf;
};

TEST_CASE("hello() says hello")
{
    std::ostringstream out;
    {
        RedirectConsole console(out);

        hello("tester");
        hello("you");
    }

    REQUIRE(out.str() == "Hello, tester!\nHello, you!\n");
}