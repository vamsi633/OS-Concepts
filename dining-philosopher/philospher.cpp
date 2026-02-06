#include <iostream>
#include <thread>
#include<mutex>
#include<vector>
#include <chrono>

class DiningTable{
    private:
    int NUM_PH;
    std::vector<std::mutex> chopsticks;
    std::mutex print_mutex;
    public:
    DiningTable(int n): NUM_PH(n), chopsticks(n){ }

    void eat(int id){

        int left=id;
        int right=(id+1)%NUM_PH;

        {
            std::scoped_lock lock(chopsticks[left],chopsticks[right]);
            // Critical section: both chopsticks held → eating
            {
                std::scoped_lock print_lock(print_mutex);
                std::cout << "Philosopher " << id << " is eating...\n";
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
        }

       // chopsticks released here

        {
            std::scoped_lock print_lock(print_mutex);
            std::cout << "Philosopher " << id << " is thinking.\n";
        }
    }
    
};

int main(){
int n=7;
DiningTable table(n);

std::vector<std::thread> philosophers;

for(int i=0;i<n;i++){
    philosophers.push_back(std::thread(&DiningTable::eat,&table,i));
}

for(auto& t: philosophers){
    t.join();
}

return 0;
}