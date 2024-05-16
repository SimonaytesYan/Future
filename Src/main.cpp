#include <thread>

#include "Expected.h"

#include "Future.h"
#include "Promise.h"

int main()
{
    Promise<int> promise;
    Future<int> future = promise.MakeFuture();

    std::thread([&promise]
                {
                    int counter = 0;
                    while(counter != INT_MAX)
                    { counter++; }

                    promise.SetValue(9); 
                    fprintf(stderr, "SetValue(9)\n");

                }).detach();

    fprintf(stderr, "Start waiting\n");
    int value = future.Get();
    fprintf(stderr, "Value = %d\n", value);
}