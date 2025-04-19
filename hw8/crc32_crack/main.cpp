#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <thread>

#include <future>
#include <stdexcept>

#include "CRC32.hpp"
#include "IO.hpp"

const unsigned int t = std::thread::hardware_concurrency(); // количество потоков

/// @brief Переписывает последние 4 байта значением value
void replaceLastFourBytes(std::vector<char> &data, uint32_t value) {
  std::copy_n(reinterpret_cast<const char *>(&value), 4, data.end() - 4);
}

/**
 * @brief Формирует новый вектор с тем же CRC32, добавляя в конец оригинального
 * строку injection и дополнительные 4 байта
 * @details При формировании нового вектора последние 4 байта не несут полезной
 * нагрузки и подбираются таким образом, чтобы CRC32 нового и оригинального
 * вектора совпадали
 * @param original оригинальный вектор
 * @param injection произвольная строка, которая будет добавлена после данных
 * оригинального вектора
 * @return новый вектор
 */
void hack(int id, const std::vector<char> &original,
          const std::string &injection, size_t begin_val, size_t end_val, 
          const char *output, std::promise<void> &&promise) {

  bool flag = false;

  const uint32_t originalCrc32 = crc32(original.data(), original.size());

  std::vector<char> result (original.size() + injection.size() + 4);

  auto it = std::copy(original.begin(), original.end(), result.begin());
  std::copy(injection.begin(), injection.end(), it);

  /*
   * Внимание: код ниже крайне не оптимален.
   * В качестве доп. задания устраните избыточные вычисления
   */

  try { 
    for (size_t i = begin_val; i < end_val; ++i) {
      // Заменяем последние четыре байта на значение i
      replaceLastFourBytes(result, uint32_t(i));
      // Вычисляем CRC32 текущего вектора result
      auto currentCrc32 = crc32(result.data(), result.size());

      if (currentCrc32 == originalCrc32) {
        flag = true;

        writeToFile(output, result);

        promise.set_value();

        return;
      }

      // Отображаем прогресс
      /* if (i % 1000 == 0) {
        std::cout << "progress: "
              << static_cast<double>(i) / static_cast<double>(end_val)
              << std::endl;
      }*/
    }

    if(!flag)
      throw std::logic_error("Can't hack"); 

    } catch(...) {
      promise.set_exception(std::current_exception());
    }
}


int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Call with two args: " << argv[0]
              << " <input file> <output file>\n";
    return 1;
  }

  // Создание promise для передачи результата
  std::vector <std::promise<void>> promises(t);
  // Получение future для проверки результатов
  std::vector <std::future<void>> futures;
  // Создание вектора потоков
  std::vector <std::thread> thread_vec;

  const size_t maxVal = std::numeric_limits<uint32_t>::max();
  size_t subrange = maxVal / t;

  const std::vector<char> data = readFromFile(argv[1]);

  // Запуск потоков
  for (int i = 0; i < t; i++) {

    futures.push_back(promises[i].get_future());
    
    thread_vec.push_back(std::thread( hack, i, data, "He-he-he", i * subrange , subrange * (i + 1), argv[2], 
                        std::move(promises[i])));
  }

  // Ожидание завершения потоков и обработка исключений
  for (int i = 0; i < t; i++) {
    try {
        futures[i].get(); 
        std::cout << i << " : Success " << std::endl;
    }
    catch (const std::exception &e) {
        std::cout << i << " : " << e.what() << std::endl;
    } 
  }

  for (int i = 0; i < t; i++) {
    thread_vec.at(i).join ();
  }

  return 0;
}
