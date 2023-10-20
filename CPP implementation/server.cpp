#include <cpp_redis/cpp_redis>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

bool new_message_received = false;
std::string received_message;
std::mutex new_message_mutex;
std::condition_variable new_message_cv;

void worker_thread(cpp_redis::subscriber& sub) {
    sub.subscribe("chatroom", [](const std::string& chan, const std::string& msg) {
        std::unique_lock<std::mutex> lock(new_message_mutex);
        received_message = msg;
        new_message_received = true;
        lock.unlock();
        new_message_cv.notify_one();
    });

    sub.commit();
}

int main() {
    cpp_redis::subscriber sub;

    sub.connect("127.0.0.1", 6379, [](const std::string& host, std::size_t port, cpp_redis::connect_state status) {
        if (status == cpp_redis::connect_state::dropped) {
            std::cerr << "Subscriber disconnected from " << host << ":" << port << std::endl;
        }
    });

    std::thread worker(worker_thread, std::ref(sub));

    while (true) {
        std::unique_lock<std::mutex> lock(new_message_mutex);
        new_message_cv.wait(lock, [] { return new_message_received; });

        std::cout << "Received message: " << received_message << std::endl;

        new_message_received = false;
    }

}
