#include <fstream>
#include <iostream>
#include <algorithm>

void print_array (std::string* arr, int row)
{
for (int i = 0; i < row; ++i)
  {
    std::cout << arr[i]<< std::endl;
  }
  std::cout << std::endl;
}

void remove_characters (std::string* arr, int row)
{
  for (int i = 0; i < row; ++i)
    {
      arr[i].erase(std::remove(arr[i].begin(), arr[i].end(), ':'), arr[i].end());
    }
}

void Zero_values (std::string* arr, int row)
{
  size_t pos;
  for (int i = 0; i < row; ++i)
    {
    while ((pos = arr[i].find("0")) != std::string::npos)
      {
        arr[i].replace(pos, 1, "-");
      }
    }
}

void bubble_sorting (std::string* arr, int row)
{
  bool swapped = false;
  do
      {
          swapped = false;
          for (int i = 1; i < row; i++)
          {
             if (arr[i - 1].length() > arr[i].length())
             {
                  std::string temp = arr[i - 1];
                  arr[i - 1] = arr[i];
                  arr[i] = temp;
                  swapped = true;
             }
          }
    } while (swapped);
}

int main()
{

  int row = 0; // кол-во строк (нам не известно)
  std::ifstream file("proc/meminfo/test.txt");
  std::ofstream NewFile("proc/meminfo/out.txt");
  std::string temp;
  std::string delete_symbol = ":!";

  if (!file.is_open())
  {
    std::cout << "Couldn't open the file proc/meminfo/test.txt" << std::endl;
    return 1;
  }
  else
  {
    std::cout << "it turned out to open the file proc/meminfo/test.txt" << std::endl<< std::endl;

    while ( std::getline(file, temp))
      ++row;
    std::cout << "in the file "<< row << " lines "<< std::endl;

    file.clear();
    file.seekg(0);

    std::string* arr = new std::string[row];
    for (int i = 0; i < row && file; ++i)
    {
      file >> arr[i];
    }
    std::cout<< std::endl;
    file.close();
    print_array (arr,row);

    std::cout << "We remove all characters from the text "":"". "<< std::endl<< std::endl;
    remove_characters(arr,row);
    print_array (arr,row);

    std::cout << "Zero values are replaced by a dash."<< std::endl<< std::endl;
    Zero_values (arr,row);
    print_array (arr,row);

    std::cout << "Sorting the rows by memory size."<< std::endl<< std::endl;
    bubble_sorting (arr,row);
    print_array (arr,row);

    std::cout << "We will write the result to a new file proc/meminfo/out.txt"<< std::endl<< std::endl;

    if (!NewFile.is_open())
    {
      std::cout << "Couldn't open the file proc/meminfo/out.txt" << std::endl;
      return 1;
    }
    else
    {
    for (int i = 0; i < row; i++ )
      {
        NewFile << arr[i] << std::endl;
      }
    std::cout << "Successfully written to a file proc/meminfo/out.txt" << std::endl;
  }
  NewFile.close();
  delete[] arr;
  }
}
