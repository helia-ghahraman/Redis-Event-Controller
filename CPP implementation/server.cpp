#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <sw/redis++/redis++.h>

bool new_message_received = false;
std::string received_message;
std::mutex new_message_mutex;
std::condition_variable new_message_cv;

void worker_thread() {
    std::string channel = "chatroom";

    sw::redis::ConnectionOptions connection_options;
    connection_options.host = "127.0.0.1";
    connection_options.port = 6379;

    try {
        auto redis1 = sw::redis::Redis(connection_options);
        auto sub = redis1.subscriber();

        sub.subscribe(channel);

//        , [&channel](const std::string& chan, const std::string& msg) {
//            if (chan == channel) {
//                std::unique_lock<std::mutex> lock(new_message_mutex);
//                received_message = msg;
//                new_message_received = true;
//                lock.unlock();
//                new_message_cv.notify_one();
//            }
//        }
        sub.consume();
    } catch (const std::exception& e) {
        std::cerr << "Exception in worker thread: " << e.what() << std::endl;
    }
}

int main() {
    std::thread worker(worker_thread);

    while (true) {
        std::unique_lock<std::mutex> lock(new_message_mutex);
        new_message_cv.wait(lock, [] { return new_message_received; });

        std::cout << "Received message: " << received_message << std::endl;

        new_message_received = false;
    }

}
