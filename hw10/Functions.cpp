#include "Functions.h"
#include <regex>

// Функция генерации гаммы
std::string gamma_generate(std::size_t length) {
    std::string result;
    result.resize(length);
 
    for(size_t i = 0; i < result.size(); ++i) {
        result[i] = static_cast<char>(rand() % 256);
    }
    return result;
}

// Функция гаммa - шифрования
std::string gamma_cipher(const std::string& data, const std::string& key) {
    std::string result = data;
    for(size_t i = 0; i < data.size(); ++i) {
        result[i] = data[i] ^ key[i % key.size()];
    }
    return result;
}; 

// Функция записи истории чата в файл
void log_message(const std::string& msg, const std::string& direction, const std::string& name) {
    std::ofstream outfile(LOG_FILENAME, std::ios::app);
    if(!outfile) {
        std::cout << "Не удалось открыть файл " << LOG_FILENAME << " для записи." << std::endl;
        return;
    }

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    char time_str[100];
    std::strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", std::localtime(&now_time));
  
    outfile << "[" << time_str << "] " << "[" << name << "] " << "[" << direction << "] " << msg << "\n"; 
    outfile << "-----\n";

    outfile.close();
};

// Функция проверки корректности ввода номера порта
bool valid_port(const int& port) {
    if (port < 1 || port > 65535)
        return false;
    return true;
}

// Функция проверки корректности ввода ip-адресса
bool valid_ip_adress(const std::string& ip) {
    std::string substr[4];
    int number;

    std::regex ip_regex("^(?:[0-9]{1,3}\\.){3}[0-9]{1,3}$"); 

    if (!std::regex_match(ip, ip_regex)) {
        return false;
    }
    
    int j = 0;
    for (char i: ip) {
        if (i != '.') {
            substr[j] += i;
        } else {
            j ++;
            continue;
        }
    }

    for(int k = 0; k < 4; ++k) {
        number = stoi(substr[k]);
        if (number < 0 || number > 255) {
            return false;
        }
    }
    return true;
};