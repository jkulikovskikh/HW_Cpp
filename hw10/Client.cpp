#include "Client.h"
#include <string>
#include <cctype>

Client::Client(asio::io_context& io_context, const std::string& ip, const int port, const std::string& name)
    : socket_(io_context) { 
    try {
        username = name;
        for (size_t i = 0; i < name.size(); ++i) {
            username[i] = std::tolower(static_cast<unsigned char>(username[i]));
        }
        if (username == NAME_SERVER) {
            std::cout << "Клиент не может иметь имя " << NAME_SERVER << 
            ". Пожалуйста, выберите другое имя." << std::endl; 
            exit(1); 
        }

        socket_.connect(tcp::endpoint(asio::ip::make_address(ip), port)); // Подключение к серверу
        username = name;

        std::cout << "Клиент успешно подключился к серверу!" << std::endl; 
    } catch (std::exception& e) {
        std::cerr << "Ошибка подключения: " << e.what() << std::endl; 
        exit(1); 
    }
}

void Client::run() {
   // Запускаем поток для приема сообщений
    std::thread read_thread(&Client::receive_message, this);

    send_message();

    read_thread.join();
}

void Client::receive_message() {
    while (true) {
        try {
             // Читаем
            char length_buf[4];
            asio::read(socket_, asio::buffer(length_buf, 4));
            uint32_t msg_length = ntohl(*reinterpret_cast<uint32_t*>(length_buf));

            std::vector<char> buf(msg_length);
            asio::read(socket_, asio::buffer(buf.data(), msg_length));
            std::string msg(buf.begin(), buf.end());

            // Расшифровываем
            std::string key = gamma_generate(msg.size());
            std::string decrypted_msg = gamma_cipher(msg, key); 

            std::cout << "Получено: " << decrypted_msg << std::endl;
            log_message("[decrypted]: " + decrypted_msg, "received", username);

        } catch (std::exception& e) {
            std::cerr << "Ошибка при получении сообщения: " << e.what() << std::endl;
            break; 
        }
    }
}

void Client::send_message() {
    std::string msg;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "Для выхода введите 'q'" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    while (true) {
        std::getline(std::cin, msg); 
        if (!msg.empty() && msg != "q") {
            try {
                // Зашифровываем
                std::string key = gamma_generate(msg.size());
                std::string encrypted_msg = gamma_cipher(msg, key); 

                log_message("[decrypted]: " + msg, "sent", username);
                log_message("[encrypted]: " + encrypted_msg, "sent", username);

                // Отправляем
                uint32_t reply_length = htonl(static_cast<uint32_t>(encrypted_msg.size()));
                asio::write(socket_, asio::buffer(&reply_length, 4));
                asio::write(socket_, asio::buffer(encrypted_msg.data(), encrypted_msg.size())); 

            } catch (std::exception& e) {
                std::cerr << "Ошибка при отправлении сообщения: " << e.what() << std::endl;
                break; // Выходим из цикла при ошибке
            }
        } 
        else {
            break;
        }
    }
    socket_.close();
    std::cout << "Соединение закрыто." << std::endl;
}