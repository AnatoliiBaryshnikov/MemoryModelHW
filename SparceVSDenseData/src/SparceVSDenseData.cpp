// SparceVSDenseData.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 

#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <array>

const std::vector< std::vector<int>> get_random_sparsed_2d_array(int _2d_array_size, double sparce_coef);

int main()
  {
  const int _2d_array_size = 5000;
  double sparse_coeff = 0.00;
  double sparse_coeff_increment = 0.01; 

  for (int counter = 0; counter < 20; ++counter)
    {
    sparse_coeff += sparse_coeff_increment;
    std::cout << "sparse_coeff = [" << sparse_coeff << "]\n";

    const std::vector< std::vector<int>> _2d_array = get_random_sparsed_2d_array(_2d_array_size, sparse_coeff);

    /*for (size_t i = 0; i < _2d_array_size; i++) // this is for debug purposes
      {
      for (size_t j = 0; j < _2d_array_size; j++)
        {
        std::cout << _2d_array[i][j] << " ";
        }
      std::cout << std::endl;
      }*/

    std::vector<std::pair<std::array<int, 2>, int>> vector_to_save_coord; // I`ve tried to put vector and map in equal conditions,
                                                                          // so vector also contains pairs like ([x,y], value).
                                                                          // However I`m not sure that this is what exactly needed)
    std::map<std::array<int, 2>, int> map_to_save_coord;

    auto start1 = std::chrono::system_clock::now();
    for (int i = 0; i < _2d_array_size; i++)
      {
      for (int j = 0; j < _2d_array_size; j++)
        {
        std::array<int, 2> coord = { i,j };
        int value = _2d_array[i][j];
        vector_to_save_coord.push_back(std::make_pair(coord, value)); // adding all to vector
        }
      }
    auto end1 = std::chrono::system_clock::now();
    std::chrono::duration<int64_t, std::nano> time1 = end1 - start1;
    std::cout << "...adding all sparsed data to vector \n "
      << time1.count() / 1000000 << " ms\n";

    auto start2 = std::chrono::system_clock::now();
    for (int i = 0; i < _2d_array_size; i++)
      {
      for (int j = 0; j < _2d_array_size; j++)
        {
        std::array<int, 2> coord = { i,j };
        int value = _2d_array[i][j];
        if (value == 1)
          {
          map_to_save_coord.insert(std::make_pair(coord, value)); // adding only 1-s to map
          }
        }
      }
    auto end2 = std::chrono::system_clock::now();
    std::chrono::duration<int64_t, std::nano> time2 = end2 - start2;
    std::cout << "...adding only \"1\"-s from sparsed data to map \n "
      << time2.count() / 1000000 << " ms\n\n";
    }

  system("pause");
  }

/// <summary>
/// This function creates a 2d array (vector of vectors, to be more precise) with given size
/// and randomly fills it with 1-s with given density.
/// </summary>
/// <param name="_2d_array_size"> - size of 2d array</param>
/// <param name="sparce_coef"> - fraction of 1-s from total amount of cells </param>
/// <returns></returns>
const std::vector< std::vector<int>> get_random_sparsed_2d_array(int _2d_array_size, double sparce_coef)
  {
  std::vector<std::vector<int>> _2d_array(_2d_array_size, std::vector<int>(_2d_array_size));

  if (sparce_coef > 1)
    {
    std::cout << "Sparce coefficient is too large. Corrected to 1.0\n";
    sparce_coef = 1.0;
    }

  if (sparce_coef < 0)
    {
    std::cout << "Sparce coefficient is negative. Corrected to 0.0\n";
    sparce_coef = 0.0;
    }

  srand((unsigned)time(0));
  int random_x;
  int random_y;

  int number_of_ones_in_2d_Array = _2d_array_size * _2d_array_size * sparce_coef;
  while (number_of_ones_in_2d_Array > 0)
    {
    random_x = rand() % _2d_array_size;
    random_y = rand() % _2d_array_size;

    if (_2d_array[random_x][random_y] == 0)
      {
      _2d_array[random_x][random_y] = 1;
      --number_of_ones_in_2d_Array;
      continue;
      }

    }

  return _2d_array;
  }