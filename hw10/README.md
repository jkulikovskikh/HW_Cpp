# Описание программы “Мессенджер с реализацией гамма-шифрования”

## Назначение программы

 “Мессенджер с реализацией гамма-шифрования” представляет собой консольное клиент-серверное приложение (программу), позволяющее пользователям обмениваться зашифрованными сообщениями с использованием алгоритма гамма-шифрования. 

## Основные функции

-	Отправка и получение сообщений\
Пользователи могут отправлять и получать сообщения в реальном времени. Взаимодействие по сети синхронное.
-	Гамма-шифрование\
Применяется алгоритм гамма-шифрования для шифрования сообщений перед отправкой, а также для расшифровки полученных сообщений. 
-	Сохранение истории сообщений\
История сообщений сохраняется в текстовый файл.
-	Проверка корректности данных вводимых пользователем\
Проверяется корректность вводимого пользоваетелем ip-адресса и порта.

## Технические требования

-	Реализовать программу на современном стандарте C++ (C++17 и выше).
-	Для сборки программы использовать CMake.
-	Использовать стандартные библиотеки.
-	Использовать библиотеку ASIO в режиме ASIO_STANDALONE для обмена сообщениями по сети.
-	Обеспечить интерфейс через консоль.

## Cтруктура программы

-	main.cpp – точка входа, управление меню и интерфейс.
-	Server.h/Server.cpp – класс, реализующий работу сервера.
-	Client.h/Client.cpp – класс, реализующий работу клиента.
-	Functions.h/ Functions.cpp – функции программы: гамма-шифрование, запись истории сообщений в файл, проверки корректности ввода ip-адресса и порта.
-   CMakeLists.txt – файл для сборки программы.
-	README.md – описание программы.

## Логика работы программы

1. 	Открыть два или более терминала. Для корректного отображения интерфейса программы необходимо в терминалах перед запуском сервера и клиентов установить кодировку консоли командой `chcp 65001`.
1.  В одном терминале запустить программу как сервер, указав режим (server) и порт для подключения (12345):
	`./chat server 12345`
1. В первом терминале запустится сервер и будет ждать подключения клиентов. 
1. Во втором и последующих терминалах запустить клиентов, указав режим (client), ip-адрес (“127.0.0.1”), порт для подключения (12345) и имя пользователя:
	`./chat client “127.0.0.1” 12345 Ivan`
1. После запуска клиентов, во втором и последующих терминалах программа предложит ввести сообщение или `q` для выхода. 
1. Один из Пользователей вводит сообщение.
1. Введенное сообщение шифруется и отправляется на сервер. Сервер принимает сообщение и пересылает его всем подключенным клиентам, кроме клиента, отправившего сообщение.
1. Пользователи принимают зашифрованное сообщение от сервера, расшифровывают его и выводят в консоль.
1. И так далее, пока кто-то из пользователей не введeт `q` для выхода.