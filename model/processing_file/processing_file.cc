#include "processing_file.h"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../../viewer_data.h"

namespace s21 {

ProcessingFile::ProcessingFile(const std::string file_name) {
  ReadFileProcess(file_name);
}

ProcessingFile::ProcessingFile(const char* file_name) {
  ReadFileProcess(file_name);
}

ProcessingFile& ProcessingFile::operator=(const std::string file_name) {
  ReadFileProcess(file_name);
  return *this;
}

ProcessingFile& ProcessingFile::operator=(const char* file_name) {
  ReadFileProcess(file_name);
  return *this;
}

void ProcessingFile::AutosaveWriting(Autosave data) {
  std::ofstream outfile("settings.txt", std::ios::out | std::ios::trunc);
  if (outfile.is_open()) {
    outfile << "r " << data.radio << "\nst " << data.stipple << "\nsq "
            << data.square << "\nSL " << data.size_line << "\nSP "
            << data.size_point << "\n";
    outfile << "L " << data.red_line << " " << data.green_line << " "
            << data.blue_line << "\n";
    outfile << "P " << data.red_point << " " << data.green_point << " "
            << data.blue_point << "\n";
    outfile << "B " << data.red_backg << " " << data.green_backg << " "
            << data.blue_backg << "\n";
    outfile.close();
  }
}

void ProcessingFile::AutosaveReading(Autosave& data) {
  std::ifstream infile("settings.txt");
  if (infile.is_open()) {
    std::string line;
    while (std::getline(infile, line)) {
      std::stringstream ss(line);  // string stran
      std::string key;
      ss >> key;
      if (key == "r") {
        ss >> data.radio;
      } else if (key == "st") {
        ss >> data.stipple;
      } else if (key == "sq") {
        ss >> data.square;
      } else if (key == "SL") {
        ss >> data.size_line;
      } else if (key == "SP") {
        ss >> data.size_point;
      } else if (key == "L") {
        ss >> data.red_line >> data.green_line >> data.blue_line;
      } else if (key == "P") {
        ss >> data.red_point >> data.green_point >> data.blue_point;
      } else if (key == "B") {
        ss >> data.red_backg >> data.green_backg >> data.blue_backg;
      }
    }
    infile.close();
  } else {
    throw std::runtime_error("Error");
  }
}

void ProcessingFile::ReadFileProcess(const std::string file_name) {
  Read(file_name);
}

void ProcessingFile::ReadFileProcess(const char* file_name) {
  std::string new_file_name = file_name;
  Read(new_file_name);
}

std::vector<unsigned int> ProcessingFile::get_polygons() const noexcept {
  return read_file_.get_polygons();
}

std::vector<float> ProcessingFile::get_vertexes() const noexcept {
  return read_file_.get_vertexes();
}

std::vector<unsigned int>& ProcessingFile::get_polygons() noexcept {
  return read_file_.get_polygons();
}

std::vector<float>& ProcessingFile::get_vertexes() noexcept {
  return read_file_.get_vertexes();
}

size_t ProcessingFile::GetQuantityFaces() const noexcept {
  return read_file_.GetQuantityFaces();
}

size_t ProcessingFile::GetQuantityVertexes() const noexcept {
  return read_file_.GetQuantityVertexes();
}

void ProcessingFile::Read(std::string file_name) {
  if (IsOBJFile(file_name)) {
    read_file_.ReadOBJ(open_file_.Open(file_name));
  } else {
    throw std::ios_base::failure("No correct format" + file_name);
  }
}

bool ProcessingFile::IsOBJFile(std::string file_name) {
  std::filesystem::path file_path(file_name);
  return (file_path.extension() == ".obj");
}

}  // namespace s21
