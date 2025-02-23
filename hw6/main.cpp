#include <iostream>
#include <vector>
#include "containers.h"

using namespace std;

void test_serial_container() {

	SerialContainer<int> container_serial;

	// Заполнение контейнера
	for (int i = 0; i < 10; ++i) {
		container_serial.push_back(i);	
	}

	// Вывод содержимого контейнера на экран
	std::cout << "--------serial container--------" << std::endl;
	container_serial.print();
	std::cout << std::endl;

	// Вывод размера контейнера на экран
	std::cout << container_serial.size() << std::endl;

	// Удаление третьего (по счёту), пятого и седьмого элементов 
	int pos[3] = {3, 5, 7};
	container_serial.erase_positions(pos, std::size(pos));
	// Вывод содержимого контейнера на экран 
	container_serial.print();
	std::cout << std::endl;

	// Добавление элемента 10 в начало контейнера
	container_serial.insert_to_begin(10);
	// Вывод содержимого контейнера на экран 
	container_serial.print();
	std::cout << std::endl;

	// Добавление элемента 20 в середину контейнера
	container_serial.insert_to_position(20, 4);
	// Вывод содержимого контейнера на экран 
	container_serial.print();
	std::cout << std::endl;

	// Добавление элемента 30 в конец контейнера
	container_serial.insert_to_end(30);
	// Вывод содержимого контейнера на экран 
	container_serial.print();
	std::cout << std::endl;
}

void test_list_type_containers() {

	ListTypeContainer<int> container_list_type;

	// Заполнение контейнера
	for (int i = 0; i < 10; ++i) {
		container_list_type.push_back(i);	
	}

	// Вывод содержимого контейнера на экран
	std::cout << "-------list type container------" << std::endl;
	container_list_type.print();
	std::cout << std::endl;	

	// Вывод размера контейнера на экран
	std::cout << container_list_type.size() << std::endl;

	// Удаление третьего (по счёту), пятого и седьмого элементов (по хранимому объекту) 
	int value[3] = {2, 4, 6};
	container_list_type.erase_values(value, std::size(value));
	// Вывод содержимого контейнера на экран 
	container_list_type.print();
	std::cout << std::endl;	

	// Добавление элемента 10 в начало контейнера
	container_list_type.insert_to_begin(10);
	// Вывод содержимого контейнера на экран 
	container_list_type.print();
	std::cout << std::endl;	

	// Добавление элемента 20 в середину контейнера
	container_list_type.insert_to_before_value(20, 5);
	// Вывод содержимого контейнера на экран 
	container_list_type.print();
	std::cout << std::endl;	

	// Добавление элемента 30 в конец контейнера
	container_list_type.insert_to_end(30);
	// Вывод содержимого контейнера на экран 
	container_list_type.print();
	std::cout << std::endl;	

}

int main() {

	test_serial_container();
	test_list_type_containers();

	return 0;
}