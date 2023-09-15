#include <algorithm>
#include <fstream>
#include <iostream>

void print_array(std::string **arr, int row, int column) {
  std::cout << std::endl;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; ++j) {
      std::cout << arr[i][j] << "\t";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void remove_characters(std::string **arr, int row, int column) {
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; ++j) {
      arr[i][j].erase(std::remove(arr[i][j].begin(), arr[i][j].end(), ':'),
                      arr[i][j].end());
    }
  }
}

void Zero_values(std::string **arr, int row, int column) {
  size_t pos;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; ++j) {
      if (arr[i][j].length() == 1) {
        while ((pos = arr[i][j].find("0")) != std::string::npos) {
          arr[i][j].replace(pos, 1, "-");
        }
      }
    }
  }
}

void bubble_sorting(std::string **arr, int row, int column) {
  bool swapped = false;
  do {
    swapped = false;
    for (int i = 1; i < row; i++) {
      if (std::atoi(arr[i - 1][1].c_str()) > std::atoi(arr[i][1].c_str())) {
        std::string temp_0 = arr[i - 1][0];
        std::string temp_1 = arr[i - 1][1];
        std::string temp_2 = arr[i - 1][2];
        arr[i - 1][0] = arr[i][0];
        arr[i - 1][1] = arr[i][1];
        arr[i - 1][2] = arr[i][2];
        arr[i][0] = temp_0;
        arr[i][1] = temp_1;
        arr[i][2] = temp_2;
        swapped = true;
      }
    }
  } while (swapped);
}

void delete_arr(std::string **arr, int row, int column) {
  for (int i = 0; i < column; ++i)
    delete[] arr[i];
  delete[] arr;
}

int main() {

  setlocale(LC_ALL, "Russian");
  int row = 0; // кол-во строк (нам не известно)
  int column = 3;
  std::ifstream file("/proc/meminfo");
  std::ofstream NewFile("/home/su/Desktop/meminfo");
  std::string temp;
  std::string delete_symbol = ":!";

  if (!file.is_open()) {
    std::cout << "Не получилось открыть файл proc/meminfo/test.txt"
              << std::endl;
    return 1;
  } else {
    std::cout << "получилось открыть файл proc/meminfo" << std::endl
              << std::endl;
    std::cout << "Содержимое файла proc/meminfo" << std::endl
              << std::endl;
    while (std::getline(file, temp)) {
      std::cout << temp << std::endl;
      ++row;
    }
    std::cout << std::endl
              << "в файле: " << row << " строк " << std::endl
              << std::endl;

    file.clear();
    file.seekg(0);

    std::string **arr = new std::string *[row];
    for (int i = 0; i < row; i++) {
      arr[i] = new std::string[column];
    }

    for (int i = 0; i < row && file; ++i) {
      for (int j = 0; j < column && file; ++j) {
        file >> arr[i][j];
      }
    }

    file.close();

    std::cout << "Удаляем из текста все символы "
                 ":"
                 ". "
              << std::endl;
    remove_characters(arr, row, column);
    print_array(arr, row, column);

    std::cout << "Сортируем строки по объему памяти." << std::endl;
    bubble_sorting(arr, row, column);
    print_array(arr, row, column);

    std::cout << "Нулевые значения заменяем на прочерк." << std::endl;
    Zero_values(arr, row, column);
    print_array(arr, row, column);

    std::cout << "Результат запишем в новый файл p/home/su/Desktop/meminfo"
              << std::endl
              << std::endl;

    if (!NewFile.is_open()) {
      std::cout << "Не получилось открыть файл /home/su/Desktop/meminfo"
                << std::endl;
      return 1;
    } else {
      for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
          NewFile << arr[i][j] << " ";
        }
        NewFile << std::endl;
      }

      std::cout << "Успешно записали в файл p/home/su/Desktop/meminfo" << std::endl;
    }
    NewFile.close();
    delete_arr(arr, row, column);
  }
}
