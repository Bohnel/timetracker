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

  std::string argument(argv[2]);
  std::string start("-s");
  std::string end("-e");
  std::string watch("-w");

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
        if (strptime(cell.c_str(), "%a %b %d %T %Y", &timeInfoOrig) !=
            nullptr) {
          char outputBuffer[80];
          strftime(outputBuffer, sizeof(outputBuffer), "%Y-%m-%d %H:%M:%S",
                   &timeInfoOrig);
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
    oss << currentTimeStr << ", " << argv[1] << "\n";

    std::string csvData = oss.str();
    outputFile << csvData;
    outputFile.close();

  } else if (argument.compare(end) == 0) {

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
        if (strptime(cell.c_str(), "%a %b %d %T %Y", &timeInfoOrig) !=
            nullptr) {
          char outputBuffer[80];
          strftime(outputBuffer, sizeof(outputBuffer), "%Y-%m-%d %H:%M:%S",
                   &timeInfoOrig);
        }
        rowData.push_back(cell);
      }
    }

    inputFile.close();

    std::ofstream outputFile("timetracker.csv", std::ios::app);

    if (!outputFile.is_open()) {
      std::cerr << "Die Datei konnte nicht geöffnet werden." << std::endl;
      return 1;
    }

    std::time_t currentTime = std::time(nullptr);
    std::string currentTimeStr = std::ctime(&currentTime);
    std::tm *timeInfo = std::localtime(&currentTime);
    std::ostringstream oss;
    oss << currentTimeStr << "," << argv[1] << "\n";
    std::string csvData = oss.str();
    outputFile << csvData;

    std::time_t timeOrig = std::mktime(&timeInfoOrig);
    std::time_t timeNow = std::mktime(timeInfo);
    std::time_t timeDifference = timeNow - timeOrig;
    int hours = timeDifference / 3600;
    int minutes = (timeDifference % 3600) / 60;
    int seconds = timeDifference % 60;
    std::cout << hours << " Stunden, " << minutes << " Minuten, " << seconds
              << " Sekunden." << std::endl;

    outputFile.close();
  } else if (argument.compare(watch) == 0) {
    std::ifstream inputFile("timetracker.csv");
    std::string line;
    if (!inputFile.is_open()) {
      std::cerr << "Die Datei konnte nicht geöffnet werden." << std::endl;
      return 1;
    }

    while (std::getline(inputFile, line)) {
      std::istringstream lineStream(line);
      std::string cell;
      std::vector<std::string> rowData;
      std::tm timeInfoOrigX = {};

      while (std::getline(lineStream, cell, ',')) {
        if (strptime(cell.c_str(), "%a %b %d %T %Y", &timeInfoOrigX) !=
            nullptr) {
          std::time_t currentTime = std::time(nullptr);
          std::time_t timeOrig = std::mktime(&timeInfoOrigX);
          std::time_t timeDifference = currentTime - timeOrig;

          int hours = timeDifference / 3600;
          int minutes = (timeDifference % 3600) / 60;
          int seconds = timeDifference % 60;

          std::cout << hours << " Stunden, " << minutes << " Minuten, "
                    << seconds << " Sekunden." << std::endl;
        }
        rowData.push_back(cell);
      }
    }

    inputFile.close();
  }

  return 0;
}
