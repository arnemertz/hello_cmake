#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>

#include "hello.h"
#include "boundedQueue.hpp"

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

TEST_CASE("Instantiate Queue")
{
    int wantedCapacity = 0;

    SECTION("size 0") 
    {
        wantedCapacity = 0;
    }

    SECTION("size 10")
    {
        wantedCapacity = 10;
    }

    SECTION("size 100") 
    {
        wantedCapacity = 100;
    }
    BoundedQueue<int> queueUnderTest{wantedCapacity};

    REQUIRE(queueUnderTest.Capacity() == wantedCapacity);
    REQUIRE(queueUnderTest.Size() == 0);
}

TEST_CASE("Enqueue Queue")
{  
    const int wantedCapacity = 10;
    BoundedQueue<int> queueUnderTest{wantedCapacity};

    const int enqueueInt = 1;
    queueUnderTest.Enqueue(enqueueInt);

    REQUIRE(queueUnderTest.Capacity() == wantedCapacity);
    REQUIRE(queueUnderTest.Size() == 1);


    const int theOtherQueueElement = 2;
    queueUnderTest.Enqueue(theOtherQueueElement);

    REQUIRE(queueUnderTest.Capacity() == wantedCapacity);
    REQUIRE(queueUnderTest.Size() == 2);

    const int firstElement = queueUnderTest.Dequeue();
    REQUIRE(queueUnderTest.Size() == 1);
    REQUIRE(queueUnderTest.Capacity() == wantedCapacity);
    REQUIRE(firstElement == enqueueInt);
    
    const int secondElement = queueUnderTest.Dequeue();
    REQUIRE(queueUnderTest.Size() == 0);
    REQUIRE(queueUnderTest.Capacity() == wantedCapacity);
    REQUIRE(secondElement == theOtherQueueElement);
}

TEST_CASE("Enqueue blocks on full queue")
{
    using namespace std::chrono_literals;

    const int wantedCapacity = 3;
    BoundedQueue<int> queueUnderTest{wantedCapacity};

    queueUnderTest.Enqueue(1);
    queueUnderTest.Enqueue(4);
    queueUnderTest.Enqueue(5);

    std::thread blockThread([&queueUnderTest](){queueUnderTest.Enqueue(7);});
    std::this_thread::sleep_for(100ms);
    
    REQUIRE(queueUnderTest.Size() == 3);
    REQUIRE(queueUnderTest.Dequeue() == 1);
    blockThread.join();
    REQUIRE(queueUnderTest.Size() == 3);

    BoundedQueue<int> largerQueue(22);
}

TEST_CASE("Dequeue blocks on empty queue")
{
    using namespace std::chrono_literals;

    const int wantedCapacity = 3;
    const int expectedElement = 42;
    const int initialValue = -4711;
    int element = initialValue; 
    BoundedQueue<int> queueUnderTest{wantedCapacity};

    std::thread blockThread([&queueUnderTest, &element](){element = queueUnderTest.Dequeue();});
    std::this_thread::sleep_for(100ms);

    REQUIRE(element == initialValue);

    queueUnderTest.Enqueue(expectedElement);
    blockThread.join();

    REQUIRE(queueUnderTest.Size() == 0);
    REQUIRE(element == expectedElement);

}