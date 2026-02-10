#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
std::mutex sharedMutex;

void doWorkWithMutexLock(int threadIndex){
    sharedMutex.lock();
    std::cout<<"Performing work for thread: "<<threadIndex <<"\n";
    std::cout<<"Sleeping for 1 second\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    sharedMutex.unlock();
}

void executeThreadsWithMutexLock(int numThreads){
    std::thread threads[numThreads];
    std::cout<<"Starting "<<numThreads <<" threads to use lock with shared mutex\n";
    int counter=0;

    for(int i=0;i<numThreads;i++){
        threads[i]=std::thread(doWorkWithMutexLock,i);

        std::cout << "Press a key to let program proceed\n";
        getchar();

        std::cout<<"Joining threads\n";
        for(int i=0;i<numThreads;++i){
            threads[i].join();
        }
        std::cout<<"Press a key to let program proceed\n";
        getchar();
        std::cout<<"Completed all threads\n";
    }
}
int main(int argc, char *argv[]){

}