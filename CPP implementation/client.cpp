#include <cpp_redis/cpp_redis>
#include <iostream>
#include <chrono>
#include <random>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <client_id> <message>" << std::endl;
        return 1;
    }

    std::string client_id = argv[1];
    std::string message = argv[2];

    cpp_redis::client client;

    client.connect("127.0.0.1", 6379, [](const std::string& host, std::size_t port, cpp_redis::connect_state status) {
        if (status == cpp_redis::connect_state::dropped) {
            std::cerr << "Client disconnected from " << host << ":" << port << std::endl;
        }
    });

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1000, 5000); // Adjust the range as needed

    while (true) {
        client.publish("chatroom", client_id + ": " + message);
        client.sync_commit();
        std::cout << client_id + ": " + message << std::endl;
        int sleep_duration = dis(gen); // Generate a random sleep duration
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_duration));
    }



}
