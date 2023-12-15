#ifndef CPP4_3DVIEWER_V2_0_1_MODEL_MODEL_H_
#define CPP4_3DVIEWER_V2_0_1_MODEL_MODEL_H_

#include <cstddef>

#include "../viewer_data.h"
#include "processing_file/processing_file.h"

namespace s21 {

class Model {
 public:
  Model() = default;
  Model(const Model& other) = default;
  Model(Model&& other) = default;
  ~Model() = default;
  explicit Model(const std::string file_name);
  explicit Model(const char* file_name);

  Model& operator=(const std::string file_name);
  Model& operator=(const char* file_name);

  Model& operator=(const Model& other) = default;
  Model& operator=(Model&& other) = default;

  void AutosaveWriting(Autosave data);
  void AutosaveReading(Autosave& data);

  void OpenFile(const std::string file_name);
  void OpenFile(const char* file_name);
  void OtherMethods(Coordinates& data);
  void AffineRotate(Coordinates& data);

  std::vector<unsigned int>& get_polygons() noexcept;
  std::vector<float>& get_vertexes() noexcept;
  std::vector<unsigned int> get_polygons() const noexcept;
  std::vector<float> get_vertexes() const noexcept;
  size_t GetQuantityFaces() const noexcept;
  size_t GetQuantityVertexes() const noexcept;

 private:
  ProcessingFile file_data_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_MODEL_MODEL_H_
