// Read files and prints top k word by frequency

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>

const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

Counter freq_dict;

std::string tolower(const std::string &str);

void count_words(const std::string& filename, std::mutex &mtx);

void print_topk(std::ostream& stream, const Counter&, const size_t k);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Создание вектора потоков
    std::vector <std::thread> thread_vec;
    std::mutex mtx;

    // Запуск потока
    for (int i = 1; i < argc; ++i) {

        std::ifstream input{argv[i]};

        if (!input.is_open()) {
            std::cerr << "Failed to open file " << argv[i] << '\n';
            return EXIT_FAILURE;
        }

        thread_vec.emplace_back(count_words, argv[i], ref(mtx));
    }

    for (int i = 0; i < argc - 1; ++i) {
		thread_vec[i].join();
	}

    // Вывод результата в консоль
    std::cerr << "--------tork_words_mutex------- " <<  '\n';
    print_topk(std::cout, freq_dict, TOPK);
  
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
    std::cerr << "--------tork_words_mutex------- " <<  '\n';
}

std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
};

void count_words(const std::string& filename, std::mutex &mtx) {

    Counter counter;
    std::ifstream stream(filename);

    std::string s;
    while(stream >> s) {
          ++counter[tolower(s)];
    } 

    std::lock_guard lock{mtx};
    for (const auto& c: counter) {
        freq_dict[c.first] += c.second;
    }
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                      << '\n';
        });
}