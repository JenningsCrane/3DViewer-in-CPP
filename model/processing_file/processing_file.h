#ifndef CPP4_3DVIEWER_V2_0_1_MODEL_PROCESSING_FILE_PROCESSING_FILE_H_
#define CPP4_3DVIEWER_V2_0_1_MODEL_PROCESSING_FILE_PROCESSING_FILE_H_

#include <cstddef>
#include <string>
#include <vector>

#include "../../viewer_data.h"
#include "read_file.h"
// #include "wrirting_data.h"
#include "open_file.h"

namespace s21 {

class ProcessingFile {
 public:
  ProcessingFile() = default;
  ProcessingFile(const ProcessingFile& other) = default;
  ProcessingFile(ProcessingFile&& other) = default;
  ~ProcessingFile() = default;

  explicit ProcessingFile(const std::string file_name);
  explicit ProcessingFile(const char* file_name);

  ProcessingFile& operator=(const ProcessingFile& other) = default;
  ProcessingFile& operator=(ProcessingFile&& other) = default;
  ProcessingFile& operator=(const std::string file_name);
  ProcessingFile& operator=(const char* file_name);

  void AutosaveWriting(Autosave data);
  void AutosaveReading(Autosave& data);

  void ReadFileProcess(const std::string file_name);
  void ReadFileProcess(const char* file_name);

  std::vector<unsigned int>& get_polygons() noexcept;
  std::vector<float>& get_vertexes() noexcept;

  std::vector<unsigned int> get_polygons() const noexcept;
  std::vector<float> get_vertexes() const noexcept;
  size_t GetQuantityFaces() const noexcept;
  size_t GetQuantityVertexes() const noexcept;

 private:
  ReadFile read_file_;
  OpenFile open_file_;

  void Read(std::string file_name);
  bool IsOBJFile(std::string file_name);
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_MODEL_PROCESSING_FILE_PROCESSING_FILE_H_
