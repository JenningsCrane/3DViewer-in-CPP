
#include "model.h"

#include <cstddef>

#include "../viewer_data.h"
#include "model_affine_transfer.h"

namespace s21 {

Model::Model(const std::string file_name) { OpenFile(file_name); }

Model::Model(const char* file_name) { OpenFile(file_name); }

Model& Model::operator=(const std::string file_name) {
  OpenFile(file_name);
  return *this;
}

Model& Model::operator=(const char* file_name) {
  OpenFile(file_name);
  return *this;
}

void Model::AutosaveWriting(Autosave data) { file_data_.AutosaveWriting(data); }

void Model::AutosaveReading(Autosave& data) {
  file_data_.AutosaveReading(data);
}

void Model::OpenFile(const std::string file_name) {
  file_data_.ReadFileProcess(file_name);
}

void Model::OpenFile(const char* file_name) {
  file_data_.ReadFileProcess(file_name);
}

void Model::OtherMethods(Coordinates& data) {
  std::vector<float>& vertex = file_data_.get_vertexes();
  ModelAffineTransfer affineOther;

  switch (data.state) {
    case (Affine::kCenter):
      affineOther.Center(vertex);
      break;
    case (Affine::kTranslate):
      affineOther.Translate(vertex, data);
      break;
    case (Affine::kObjectReduct):
      affineOther.ObjectReduct(vertex, data);
      break;
    case (Affine::kMaxMin):
      affineOther.CalculateMaxOrMin(vertex, data);
      break;
    case (Affine::kScale):
      affineOther.Scale(vertex, data);
      break;
    default:
      break;
  }
}

void Model::AffineRotate(Coordinates& data) {
  std::vector<float>& vertex = file_data_.get_vertexes();
  ModelAffineTransfer affineTransfer;

  switch (data.state) {
    case (Affine::kRotateX):
      affineTransfer.Rotate(RotateX(), vertex, data);
      break;
    case (Affine::kRotateY):
      affineTransfer.Rotate(RotateY(), vertex, data);
      break;
    case (Affine::kRotateZ):
      affineTransfer.Rotate(RotateZ(), vertex, data);
      break;
    default:
      break;
  }
}

std::vector<unsigned int>& Model::get_polygons() noexcept {
  return file_data_.get_polygons();
}

std::vector<float>& Model::get_vertexes() noexcept {
  return file_data_.get_vertexes();
}

// std::vector<unsigned int> Model::get_polygons() const noexcept {
//   return file_data_.get_polygons();
// }

// std::vector<float> Model::get_vertexes() const  noexcept {
//   return file_data_.get_vertexes();
// }

size_t Model::GetQuantityFaces() const noexcept {
  return file_data_.GetQuantityFaces();
}

size_t Model::GetQuantityVertexes() const noexcept {
  return file_data_.GetQuantityVertexes();
}

}  // namespace s21
