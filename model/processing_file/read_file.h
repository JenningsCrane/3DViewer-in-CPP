#ifndef CPP4_3DVIEWER_V2_0_1_MODEL_PROCESSING_FILE_READ_FILE_H_
#define CPP4_3DVIEWER_V2_0_1_MODEL_PROCESSING_FILE_READ_FILE_H_

#include <cstddef>
#include <fstream>
#include <vector>

#include "../../viewer_data.h"

namespace s21 {

class ReadFile {
 public:
  ReadFile() = default;
  ReadFile(const ReadFile& other) = default;
  ReadFile(ReadFile&& other) = default;
  ~ReadFile() = default;
  ReadFile& operator=(const ReadFile& other) = default;
  ReadFile& operator=(ReadFile&& other) = default;

  std::vector<unsigned int>& get_polygons() noexcept;
  std::vector<float>& get_vertexes() noexcept;
  std::vector<unsigned int> get_polygons() const noexcept;
  std::vector<float> get_vertexes() const noexcept;
  size_t GetQuantityFaces() const noexcept;
  size_t GetQuantityVertexes() const noexcept;

  void ReadOBJ(std::ifstream& file_stream);

 private:
  std::vector<unsigned int> polygons_;
  std::vector<float> vertexes_;

  void ReadLineInOBJFile(std::istringstream& line_elements);
  void ReadVertexInOBJFile(std::istringstream& line_elements);
  void ReadPolygonsInOBJFile(std::istringstream& line_elements);
  void ProcessReadPolygonsInOBJFile(std::string& element,
                                    std::pair<bool, size_t>& first_element);
  void WritingFromStringInUnsignedInt(const std::string element,
                                      size_t& vertex);
  void ErrorWhenReadingTheCharacter(std::istringstream& line_elements);
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_MODEL_PROCESSING_FILE_READ_FILE_H_
