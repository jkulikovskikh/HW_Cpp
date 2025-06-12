#include "Server.h"

Server::Server(asio::io_context& io_context, const int port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)),
    flag_close_(false) {
    acceptor_.listen();
    std::cout << "Сервер подключен. Ожидание подключения клиента." << std::endl;
    
    gamma = gamma_generate(SIZE_GAMMA);  // генерация длинной гаммы, общей для всех клиентов
}

void Server::run() {
    while (true) {
        try {
            auto socket = std::make_shared<tcp::socket>(acceptor_.accept());
            std::cout << "Новый клиент подключился!" << std::endl;

            send_gamma(socket);

            // Обрабатываем подключение клиента в новом потоке
            threads_.emplace_back(&Server::handle_client, this, socket); 

        } catch (...) {
            if (flag_close_)
                break;
        }
    }
}

void Server::send_gamma(std::shared_ptr<tcp::socket> socket) {
    try {
        // Отправляем
        uint32_t gamma_length = htonl(static_cast<uint32_t>(gamma.size()));
        asio::write(*socket, asio::buffer(&gamma_length, 4));
        asio::write(*socket, asio::buffer(gamma.data(), gamma.size())); 
    } catch (std::exception& e) {
        std::cout << "Ошибка при отправке гаммы клиенту: " << e.what() << std::endl;
    }
}

void Server::stop() {
    try {
        if (clients_.size() == 0) {
            std::cout << "Сервер закрыт." << std::endl;
        }
        else {
            std::cout << "Сервер будет закрыт после отключения всех клиентов." << std::endl;
        }
        flag_close_ = true;
        acceptor_.close(); // Закрываем сервер
    } catch (const std::exception& e) {
        std::cout << "Ошибка в закрытии сервера." << std::endl;
    }
}

void Server::handle_client(std::shared_ptr<tcp::socket> socket) {
    // Добавляем нового клиента в список
    clients_.push_back(socket);
    while (true) {    
        try {
            // Читаем
            char length_buf[4];

            asio::read(*socket, asio::buffer(length_buf, 4));
            uint32_t msg_length = ntohl(*reinterpret_cast<uint32_t*>(length_buf));

            std::vector<char> buf(msg_length);
            asio::read(*socket, asio::buffer(buf.data(), msg_length));
            std::string encrypted_msg(buf.begin(), buf.end());
           
            // Печатаем сообщение от клиента
            log_message("[encrypted]: " + encrypted_msg, "received", "server");
            
            // Отправляем это сообщение всем остальным клиентам
            broadcast_message(encrypted_msg, socket);

        } catch (std::exception& e) {
            std::cout << "Ошибка при чтении сообщения от клиента: " << e.what() << std::endl;
            break;
        }  
    }
    // Удаляем клиента, если он отключился
    clients_.erase(std::remove(clients_.begin(), clients_.end(), socket), clients_.end());  
    socket->close();
    std::cout << "Клиент отключился." << std::endl;
    if (clients_.size() == 0 && flag_close_) {
         std::cout << "Сервер закрыт." << std::endl;
    }
}

void Server::broadcast_message(const std::string& message, std::shared_ptr<tcp::socket> sender) {
    for (const auto& client_socket : clients_) {
        // Проверяем, что это не тот же клиент
        if (client_socket != sender) {
            try {
                // Отправляем
                uint32_t reply_length = htonl(static_cast<uint32_t>(message.size()));
                asio::write(*client_socket, asio::buffer(&reply_length, 4));
                asio::write(*client_socket, asio::buffer(message.data(), message.size())); 

                log_message("[encrypted]: " + message, "sent", "server");

            } catch (std::exception& e) {
                std::cout << "Ошибка при отправке сообщения клиенту: " << e.what() << std::endl;
            }
        }
    }
}

Server::~Server() {
    for (auto& thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}
