#include <thread>

#include "Expected.h"

#include "Future.h"
#include "Promise.h"

void Test1()
{
    Promise<int> p;
    Future<int> f = p.MakeFuture();

    p.SetValue(42);

    assert(f.Get() == 42);

    printf("OK\n");
}

struct TestException 
{ };

void Test2()
{
    Promise<int> p;
    auto f = p.MakeFuture();

    try 
    {
      throw TestException();
    } 
    catch (...) 
    {
        p.SetException(std::current_exception());
    }

    try
    {
        f.Get();
    }
    catch(const TestException& exception)
    {
        printf("OK\n");
        return;
    }

    assert(false);
}

void Test3()
{
    const int real_value = 9;
    Promise<int> promise;
    Future<int> future = promise.MakeFuture();

    clock_t time_start = clock();
    std::thread([&promise]
                {
                    int counter = 0;
                    while(counter != INT_MAX)
                    { counter++; }

                    promise.SetValue(real_value);

                }).detach();

    int value = future.Get();
    clock_t time_end = clock();

    assert(value == real_value);
    assert((double)(time_end - time_start)/CLOCKS_PER_SEC > 1);
    
    printf("OK\n");
}

void Test4()
{
    Promise<std::string> p;
    auto f = p.MakeFuture();

    clock_t time_start = clock();
    std::thread([&p] 
                {
                    try 
                    {
                        int counter = 0;
                        while(counter != INT_MAX)
                        { counter++; }

                        throw TestException();
                    } 
                    catch (...) 
                    {
                        p.SetException(std::current_exception());
                    }
                }).detach();
    try
    {
        f.Get();
    }
    catch(const TestException& exception)
    {
        clock_t time_end = clock();
        assert((double)(time_end - time_start)/CLOCKS_PER_SEC > 1);
        printf("OK\n");
        return;
    }
    
    assert(false);
}

int main()
{

    Test1();
    Test2();
    Test3();
    Test4();
}