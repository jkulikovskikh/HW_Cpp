#include "Server.h"
#include "Client.h"

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "Запустите как:\n"
                  << "- сервер: " <<  argv[0] << " server " << "12345" << "\n"
                  << "- клиент: " <<  argv[0] << " client "  << "127.0.0.1 " << "12345" << "username" << "\n";
        return 1;
    }

    int port;
    std::string ip_adress;
    std::string mode = argv[1];

    asio::io_context io_context; 

    if (mode == "server") {

        if (argc < 3) {
            std::cout << "Запустите как: " 
                      <<  argv[0] << " server " << "12345" << "\n";
            return 1;
        }

        port = std::stoi(argv[2]);
        if (!valid_port(port)) {
            std::cout << "Некорректный номер порта: " << port << std::endl;
            return 1;
        }

        Server server(io_context, port);

        std::thread server_thread([&server](){ 
            server.run();
        });

        std::cout << "----------------------------------------------------" << std::endl;
        std::cout << "Для остановки сервера нажмите Enter" << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        std::cin.get();

        server.stop();

        server_thread.join();
        
    } else if (mode == "client") {

        if (argc < 5) {
            std::cout << "Запустите как: " 
                      << argv[0] << " client "  << "127.0.0.1 " << "12345" << "username" << "\n";
            return 1;
        }

        ip_adress = argv[2];
        if (!valid_ip_adress(ip_adress)) {
             std::cout << "Некорректный ip-adress: " << ip_adress << std::endl;
             return 1;
        }

        port = std::stoi(argv[3]);
        if (!valid_port(port)) {
            std::cout << "Некорректный номер порта: " << port << std::endl;
            return 1;
        }

        std::string name = argv[4];

        Client client(io_context, ip_adress, port, name); 
        client.run(); 
        
    } else {
        std::cerr << "Неккоректный режим: " << mode << std::endl;
        return 1;
    }

    return 0;
}
