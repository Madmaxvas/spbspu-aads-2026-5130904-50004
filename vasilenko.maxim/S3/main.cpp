#include "commands.hpp"
#include <iostream>

int main(int argc, char** argv)
{
  if (argc < 2) {
    std::cerr << "Error: filename required\\n";
    return 1;
  }

  vasilenko::AppContext app;
  try {
    app.parseInitialFile(argv[1]);
  } catch (const std::exception &e) {
    std::cerr << "File processing error: " << e.what() << "\\n";
    return 1;
  }

  app.runInteractive();

  return 0;
}
