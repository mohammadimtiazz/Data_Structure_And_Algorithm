#include <iostream>
#include <thread>
#include <vector>
#include <future>

// function pointer
void task_one(int num) {
  for (int i = 0; i < num; i++) {
    std::cout << "Running task one" << std::endl;
  }
}

// function object
class task_two {
 public:
  void operator()(int num) {
    for (int i = 0; i < num; i++) {
      std::cout << "Running task two" << std::endl;
    }
  }
};

int main() {
  std::cout << "Running thread one, two and three operation independently"
            << std::endl;

  // This thread is launched by using function parameters as callable
  std::thread t_obj_1(task_one, 3);

  // This thread is launched by using function object as callable
  std::thread t_obj_2(task_two(), 3);

  // define a lambda expression
  auto task_three = [](int num) {
    for (int i = 0; i < num; i++) {
      std::cout << "Running task three" << std::endl;
    }
  };

  // This thread is launched by using lambda expression as callable
  std::thread t_obj_3(task_three, 3);

  // Wait for thread to finish task one
  t_obj_1.join();
  // Wait for thread to finish task two
  t_obj_2.join();
  // Wait for thread to finish task three
  t_obj_3.join();

  // another lambda expression example
  auto task_five = [](std::vector<int> &v, unsigned int start,
                      unsigned int end) {
    int acum = 0;
    for (unsigned int i = start; i < end; i++) {
      acum = acum + v[i];
    }
    return acum;
  };

  std::vector<int> container = {1,2,3,4,5,6,7,8,9,10};
  int acum1 = 0, acum2 = 0;

  // These threads are launched by using lambda expression as callable
  auto t_obj_4 =
      std::async(task_five, std::ref(container), 0, container.size() / 2);
  auto t_obj_5 = std::async(task_five, std::ref(container),
                            container.size() / 2, container.size());

  // Wait for thread to finish task one
  acum1 = t_obj_4.get();
  // Wait for thread to finish task one
  acum2 = t_obj_5.get();

  std::cout << "acum 1 is: " << acum1 << std::endl;
  std::cout << "acum 2 is: " << acum2 << std::endl;
  std::cout << "acum 1 + 2 is: " << acum1+acum2 << std::endl;

      return 0;
}