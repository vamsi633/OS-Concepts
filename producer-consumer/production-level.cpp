
#include <condition_variable>
#include <mutex>
#include <thread>
#include <deque>
#include <iostream>
class KitchenCounter{
private:
    std::deque<int> buffer;
    size_t capacity;
    std::mutex mtx;
    std::condition_variable cv_full;
    std::condition_variable cv_empty;

public:
    KitchenCounter(size_t cap):capacity(cap){}
    void add_plate(int id){
        std::unique_lock<std::mutex> lock(mtx);
       while(buffer.size()>=3){
        cv_full.wait(lock);
       }

        buffer.push_back((id));
        std::cout<<"Chef added" <<id << std::endl;

        lock.unlock();
        cv_empty.notify_one();
    }

    int take_plate(){
        std::unique_lock<std::mutex> lock(mtx);

        while(buffer.empty()){
            cv_empty.wait(lock);
        }
        int id=buffer.front();
        buffer.pop_front();
        std::cout<<"Server took plate: "<<id<<std::endl;

        lock.unlock();
        cv_full.notify_one();

        return id;
    }

};

int main(){
    KitchenCounter counter(3);

    std::thread chef([&counter](){
        for(int i=0;i<10;i++) counter.add_plate(i);
    });

    std::thread server([&counter]() {
        for(int i=0; i<10; i++) counter.take_plate();
    });

    chef.join();
    server.join();
    return 0;
}