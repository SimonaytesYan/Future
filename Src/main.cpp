#include <thread>

#include "Future.h"
#include "Promise.h"

int main()
{
    Promise<int> promise;
    Future<int> future = promise.MakeFuture();

    std::thread([&promise]
                {
                    int counter = 0;
                    while(counter != 5000)
                    {
                        printf("cnt = %d\n", counter);
                    }
                    promise.SetValue(9); 
                }).detach();

    printf("Start waiting\n");
    int value = future.Get();
    printf("Value = $d\n", value);
}