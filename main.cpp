#include "parser.h"

int main()
{  
   setlocale(LC_ALL, "Russian");

   try
   {
      std::locale loc(".866");
      std::wcin.imbue(loc);

      std::wstring fileName;
      std::cout << "¬ведите путь к html-файлу: ";
      std::getline(std::wcin, fileName);

      Parser parser(fileName);
      parser.parse();
      parser.print();
   }
   catch (const std::exception& ex)
   {
      std::cerr << ex.what() << std::endl;
      return EXIT_FAILURE;
   }
   catch (...)
   {
      std::cerr << "Something goes wrong." << std::endl;
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}