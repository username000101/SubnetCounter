#if defined(_WIN32)
#include <Windows.h>
#endif

#include <cmath>
#include <clocale>
#include <iostream>
#include <string>

int get_hosts_by_mask(int bytes_in_mask) {
	return std::pow(2, 32 - bytes_in_mask) - 2;
}

int get_bytes_to_add_in_mask(int subnetts) {
	return std::log2(subnetts);
}

int main(int argc, char** argv) {
#if defined(_WIN32)
	SetConsoleOutputCP(CP_UTF8);
	std::setlocale(LC_ALL, "ru_RU.UTF-8");
#endif

	int bytes_to_mask = get_bytes_to_add_in_mask(std::stoi(argv[1]));
	int hosts = get_hosts_by_mask(24 + std::log2(std::stoi(argv[1])));
	std::cout << "Байт для добавления в маску: " << bytes_to_mask << std::endl;
	std::cout << "Адресов в итоговой сети(-ях): " << hosts + 2 << std::endl;
	std::cout << "Хостов в итоговой сети(-ях): " << hosts << std::endl;
	std::cout << "Тестовый IPv4: 192.168.0.0/" << 24 + bytes_to_mask << std::endl;
	std::cout << "Тестовая маска подсети: 255.255.255.0 (24)" << std::endl;

	int address = 0;
	for (int i = 0; i < std::stoi(argv[1]); ++i) {
		std::cout << "Подсеть " << i + 1 << ":" << std::endl;
		std::cout << "Адрес сети: 192.168.0." << address << "/" << 24 + bytes_to_mask << std::endl;
		std::cout << "Широковещательный адрес: 192.168.0." << address + hosts + 1 << "/" << 24 + bytes_to_mask << std::endl;
		for (int j = 1; j <= hosts; ++j) {
			std::cout << "Адрес хоста №" << j << ": 192.168.0." << address + j << " / " << 24 + bytes_to_mask << std::endl;
		}
		address += hosts + 2;
	}
}