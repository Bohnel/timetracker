#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Bitte geben Sie Argumente ein." << std::endl;
    return 1;
  }

  // for (int i = 1; i < argc; i++) {
  //   std::cout << "Argument " << i << ": " << argv[i] << std::endl;
  // }

  std::string argument(argv[2]);
  std::string start("-s");
  std::string end("-e");

  if (argument.compare(start) == 0) {
    std::ifstream inputFile("timetracker.csv");
    std::string line;
    if (!inputFile.is_open()) {
      std::cerr << "Die Datei konnte nicht geöffnet werden." << std::endl;
      return 1;
    }

    std::tm timeInfoOrig = {};
    while (std::getline(inputFile, line)) {
      std::istringstream lineStream(line);
      std::string cell;
      std::vector<std::string> rowData;

      while (std::getline(lineStream, cell, ',')) {
        // std::cout << cell << std::endl;
        if (strptime(cell.c_str(), "%a %b %d %T %Y", &timeInfoOrig) !=
            nullptr) {
          char outputBuffer[80];
          strftime(outputBuffer, sizeof(outputBuffer), "%Y-%m-%d %H:%M:%S",
                   &timeInfoOrig);

          // std::cout << timeInfo.tm_mday << ", " << timeInfo.tm_mon + 1 << ",
          // "
          // << timeInfo.tm_year << std::endl;
          // std::cout << outputBuffer << std::endl;
        }
        rowData.push_back(cell);
      }
    }

    inputFile.close();

    std::ofstream outputFile("timetracker.csv");

    if (!outputFile.is_open()) {
      std::cerr << "Die Datei konnte nicht erstellt werden." << std::endl;
      return 1;
    }

    std::time_t currentTime = std::time(nullptr);
    std::string currentTimeStr = std::ctime(&currentTime);
    std::tm *timeInfo = std::localtime(&currentTime);

    int day = timeInfo->tm_mday;
    int month = timeInfo->tm_mon + 1;
    int year = timeInfo->tm_year + 1900;
    std::cout << timeInfoOrig.tm_mday << ", " << timeInfoOrig.tm_mon + 1 << ", "
              << timeInfoOrig.tm_year + 1900 << std::endl;
    std::cout << day << ", " << month << ", " << year << std::endl;
    std::cout << year << std::endl;
    std::ostringstream oss;
    oss << currentTimeStr << "," << argv[1] << "\n";

    std::string csvData = oss.str();
    outputFile << csvData;
    outputFile.close();

    std::cout << "Die Datei wurde erfolgreich erstellt." << std::endl;
  } else if (argument.compare(end) == 0) {
    std::cout << "END" << std::endl;
  }

  return 0;
}
