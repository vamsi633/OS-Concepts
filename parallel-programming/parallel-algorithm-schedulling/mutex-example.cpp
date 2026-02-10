#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
std::mutex sharedMutex;

void doWorkWithMutexLock(int threadIndex){
    std::lock_guard<std::mutex> lock(sharedMutex);
    std::cout<<"Performing work for thread: "<<threadIndex <<"\n";
    std::cout<<"Thread "<<threadIndex<<" is sleeping for 1 second...\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void executeThreadsWithMutexLock(int numThreads){
    std::vector<std::thread> threads;
    std::cout<<"Starting Parallel Execution\n";
    int counter=0;

    for(int i=0;i<numThreads;i++){
        threads.push_back(std::thread(doWorkWithMutexLock,i));
    }
        std::cout << "All " << numThreads << " threads have been launched and are running!\n";
        std::cout << "Press a key to let program proceed\n";
        getchar();

        
        for(int i=0;i<numThreads;++i){
            if (threads[i].joinable()) { // Safety check!
            threads[i].join(); 
            }
        }
        std::cout<<"Completed all threads safely\n";
}

void doWorkWithMutexTryLock(int threadIndex){
    int attempts = 0;
    // Keep trying to get the lock without blocking the whole program
    while (!sharedMutex.try_lock()) {
        attempts++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    std::cout << "Thread " << threadIndex << " got the lock after " << attempts << " failed attempts.\n";
    sharedMutex.unlock();
}

void executeAndDetachThreadsWithMutexTryLock(int numThreads){
    std::vector<std::thread> threads;
    std::cout << "\n--- STARTING TRY_LOCK DETACHED THREADS ---\n";
    
    // 1. Actually spawn the threads (Fixing the previous bug)
    for (int i = 0; i < numThreads; ++i) {
        threads.push_back(std::thread(doWorkWithMutexTryLock, i));
    }

    // 2. Detach them immediately
    for (int i = 0; i < numThreads; ++i) {
        if (threads[i].joinable()) {
            threads[i].detach();
        }
    }
    std::cout << "Threads are now running in the background. Press ENTER to finish.\n";
    getchar();


}
int main(int argc, char *argv[]){
    int numThreads = 3;
    if (argc > 1) {
        numThreads = atoi(argv[1]);
    }

    executeThreadsWithMutexLock(numThreads);
    executeAndDetachThreadsWithMutexTryLock(numThreads);

    return 0;
}