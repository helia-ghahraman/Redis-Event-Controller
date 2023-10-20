#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <sw/redis++/redis++.h>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <client_id> <message>" << std::endl;
        return 1;
    }

    std::string client_id = argv[1];
    std::string message = argv[2];

    sw::redis::Redis client("tcp://127.0.0.1:6379"); // Create a Redis client

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 5000);
    std::string channel = "chatroom";
    std::string message1 = client_id + ": " + message;

    while (true) {
        client.publish(channel, message1); // Publish the message

        std::cout << client_id + ": " + message << std::endl;
        int sleep_duration = dis(gen); // Generate a random sleep duration
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration));
    }

    return 0;
}
