#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> counter;
void chef(){
    for(int i=0;i<5;i++){
        std::unique_lock<std::mutex> lock(mtx);
        
        while(counter.size() >=3){
            cv.wait(lock);
        }
        counter.push(i);
        std::cout<<"Chef puts plate "<< i << " down.\n";

        cv.notify_one();
    }
}

void server(){
    for(int i=0;i<5;i++){
        std::unique_lock<std::mutex> lock(mtx);
        while(counter.empty()){
            cv.wait(lock);
        }

        int plate=counter.front();
        counter.pop();
        std::cout<<"Server delivered plate " << plate <<".\n";

        cv.notify_one(); 
    }
}
int main(){
    std::thread t1(chef);
    std::thread t2(server);

    t1.join();
    t2.join();

    return 0;
}