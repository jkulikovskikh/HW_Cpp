#pragma once

#include "Functions.h"

using asio::ip::tcp;

class Client {
public:
    Client(asio::io_context& io_context, const std::string& ip, const int port, const std::string& name); 
    ~Client() {}
    
    // Основная функция
    void run();         

private:
    // Отправить сообщение серверу 
    void send_message(); 
    // Получить сообщения от сервера
    void receive_message();

    std::string username;
    tcp::socket socket_;
    std::vector<std::thread> threads_; // вектор потоков
};