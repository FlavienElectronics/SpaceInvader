#include <iostream>
#include <thread>

// Define the tasks
void task1(const std::string& message) {
	while(1)
	{
	 std::cout << "Task1 says: " << message << std::endl;
	}
   
}

void task2(const std::string& message) {
while (1)
{
std::cout << "Task2 says: " << message << std::endl;
}
    
}

int main() {
    // Create threads
    std::thread t1(task1, std::string("Hello"));
    std::thread t2(task2, std::string("Bonjourno"));

    // Wait for threads to finish
    t1.join();
    t2.join();

    return 0;
}
