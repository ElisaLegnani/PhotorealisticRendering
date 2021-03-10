#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

  if (argv[1] == NULL)
    cout << "Hello, World!" << endl;
  else
    cout << "Hello, " << argv[1] << "!" << endl;

  return 0;
}