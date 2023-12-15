#include "read_file.h"

#include <cmath>
#include <cstddef>    // size_t
#include <fstream>    //open file
#include <sstream>    //string stream
#include <stdexcept>  // std::ios_base
#include <string>
#include <vector>

#include "../../viewer_data.h"

namespace s21 {

std::vector<unsigned int>& ReadFile::get_polygons() noexcept {
  return polygons_;
}

std::vector<float>& ReadFile::get_vertexes() noexcept { return vertexes_; }

std::vector<unsigned int> ReadFile::get_polygons() const noexcept {
  return polygons_;
}

std::vector<float> ReadFile::get_vertexes() const noexcept { return vertexes_; }

size_t ReadFile::GetQuantityFaces() const noexcept {
  return polygons_.size() / 2;
}

size_t ReadFile::GetQuantityVertexes() const noexcept {
  return vertexes_.size() / 3;
}

void ReadFile::ReadOBJ(std::ifstream& file_stream) {
  polygons_.clear();
  vertexes_.clear();
  std::string line;
  while (std::getline(file_stream, line)) {
    std::istringstream line_elements(line);
    ReadLineInOBJFile(line_elements);
  }
}

void ReadFile::ReadLineInOBJFile(std::istringstream& line_elements) {
  std::string first_element;
  if (line_elements >> first_element) {
    if (first_element == "v") {
      ReadVertexInOBJFile(line_elements);
    } else if (first_element == "f") {
      ReadPolygonsInOBJFile(line_elements);
    }
  }
}

void ReadFile::ReadVertexInOBJFile(std::istringstream& line_elements) {
  float x, y, z;
  if (line_elements >> x >> y >> z) {
    vertexes_.push_back(x);
    vertexes_.push_back(y);
    vertexes_.push_back(z);
  } else {
    ErrorWhenReadingTheCharacter(line_elements);
  }
}

void ReadFile::ReadPolygonsInOBJFile(std::istringstream& line_elements) {
  std::string element;
  bool was_element = false;
  size_t num{0};  // num first element
  std::pair<bool, size_t> first_element;
  first_element = std::make_pair(was_element, num);

  while (line_elements >> element) {
    try {
      ProcessReadPolygonsInOBJFile(element, first_element);
    } catch (const std::runtime_error& e) {
      ErrorWhenReadingTheCharacter(line_elements);
    }
  }
  polygons_.push_back(first_element.second);
}

void ReadFile::ProcessReadPolygonsInOBJFile(
    std::string& element, std::pair<bool, size_t>& first_element) {
  size_t num = 0;
  size_t pos = element.find('/');
  if (pos != 0) {
    std::string first_number = element.substr(0, pos);
    WritingFromStringInUnsignedInt(first_number, num);
  } else {
    WritingFromStringInUnsignedInt(element, num);
  }
  polygons_.push_back(num);
  if (!first_element.first) {
    first_element.second = num;
    first_element.first = true;
  } else {
    polygons_.push_back(num);
  }
}

void ReadFile::WritingFromStringInUnsignedInt(const std::string element,
                                              size_t& vertex) {
  try {
    //            vertex = std::fabs(std::stoi(element)) - 1;
    int need_num = std::stoi(element);
    if (need_num < 0) {
      vertex = vertexes_.size() / 3 + need_num;
    } else {
      vertex = need_num - 1;
    }

  } catch (const std::exception& e) {
    throw std::runtime_error("Error");
  }
}

void ReadFile::ErrorWhenReadingTheCharacter(std::istringstream& line_elements) {
  std::string error("Incorrect symbol in line - \"");
  std::string line;
  std::getline(line_elements, line);
  error = error + line + "\"\n";
  throw std::runtime_error(error);
}

}  // namespace s21
