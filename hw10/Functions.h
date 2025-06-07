#pragma once

#include <asio.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <memory>
#include <algorithm>
#include <fstream>
#include <iomanip>

// Константы
const std::string LOG_FILENAME =  "log.txt";
const std::string NAME_SERVER = "server";

// Функция генерации гаммы
std::string gamma_generate(std::size_t length);

// Функция гаммa - шифрования
std::string gamma_cipher(const std::string& data, const std::string& key);

// Функция записи истории чата в файл
void log_message(const std::string& msg, const std::string& direction, const std::string& mode);

// Функция проверки корректности ввода номера порта
bool valid_port(const int& port);

// Функция проверки корректности ввода ip-адресса
bool valid_ip_adress(const std::string& ip);