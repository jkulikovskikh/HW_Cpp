#pragma once
#include "Functions.h"

using asio::ip::tcp;

class Server {
public:
    Server(asio::io_context& io_context, const int port);
    ~Server();
    
    // Основная функция    
    void run(); 
    // Остановка сервера
    void stop();

private:
    // Взаимодействие с клиентами
    void handle_client(std::shared_ptr<tcp::socket> socket);    
    // Отправка сообщения клиентам
    void broadcast_message(const std::string& message, std::shared_ptr<tcp::socket> sender); 

    tcp::acceptor acceptor_;
    std::vector<std::shared_ptr<tcp::socket>> clients_; // список клиентов
    std::vector<std::thread> threads_; // вектор для хранения потоков
    bool flag_close_; // флаг закрытия сервера
};
