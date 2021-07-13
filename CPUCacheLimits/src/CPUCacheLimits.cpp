// Cache exercise
//

#include <iostream>
#include <chrono>

int main()
{
  const int l1_cache_test_dataset_size = 64; // bytes, less than L1 size (32 KB)
  char* l1_cache_test_dataset = new char [l1_cache_test_dataset_size];
  for (size_t i = 0; i < l1_cache_test_dataset_size; i++)
    {
    l1_cache_test_dataset[i] = '1'; // filling array with meaningful data
    }

  const int l3_cache_test_dataset_size = 1311744; // bytes, larger than L2 size (1.25 MB)
  char* l3_cache_test_dataset = new char[l3_cache_test_dataset_size];
  for (size_t i = 0; i < l3_cache_test_dataset_size; i++)
    {
    l3_cache_test_dataset[i] = '1'; // filling array with meaningful data
    }

  const int mem_to_fill_size = 2000000; // bytes, block of memory to copy in
  char* mem_to_fill = new char[2000000];
  for (size_t i = 0; i < 2000000; i++)
    {
    mem_to_fill[i] = '1'; // filling array with meaningful data
    }

  long long average_for_L1 = 0;
  long long average_for_L3 = 0;
  int repeats = 6; // 
  for (size_t i = 0; i < repeats; i++) // main loop where data is copyed and time is measured
    {
    std::cout << "\n>>> Iteration " << i << "\n";

    int times_to_copy_for_L1_data = 1311744;
    auto start1 = std::chrono::system_clock::now();
    for (size_t i = 0; i < times_to_copy_for_L1_data; i++)
      {
      memcpy(l1_cache_test_dataset, mem_to_fill, l1_cache_test_dataset_size);
      }
    auto end1 = std::chrono::system_clock::now();
    std::chrono::duration<int64_t, std::nano> time1 = end1 - start1;
    std::cout << "...copying data that smaller than L1 cache size\n " 
              << time1.count() << " ns\n";
    average_for_L1 += time1.count();

    int times_to_copy_for_L3_data = 64;
    auto start2 = std::chrono::system_clock::now();
    for (size_t i = 0; i < times_to_copy_for_L3_data; i++)
      {
      memcpy(l3_cache_test_dataset, mem_to_fill, l3_cache_test_dataset_size);
      }
    auto end2 = std::chrono::system_clock::now();
    std::chrono::duration<int64_t, std::nano> time2 = end2 - start2;
    std::cout << "...copying data that larger than L2 cache size\n " 
              << time2.count() << " ns\n\n";
    average_for_L3 += time2.count();
    }

  average_for_L1 /= repeats;
  average_for_L3 /= repeats;

  std::cout << ">>> Average time for copying data that smaller than L1 cache size\n "
            << average_for_L1 << " ns" << std::endl;
  std::cout << ">>> Average time for copying data that larger than L2 cache size\n "
            << average_for_L3 << " ns" << std::endl;

  system("pause");
}
