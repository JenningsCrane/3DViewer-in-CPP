#include "controller.h"

namespace s21 {

// void Controller::Rotation(coordinates &data) { model->AffineRotate(data); }
// void Controller::SubMethods(coordinates &data) { model->OtherMethods(data); }

// void Controller::writing_data(info &data) {
//   model->parser->ProcessingFile::WriteFileProcess(data);
// }

// void Controller::read_file(info &data) {
//   model->parser->ProcessingFile::ReadFileProcess(data);
// }

void Controller::OpenFile(const std::string file_name) {
  model->OpenFile(file_name);
}
void Controller::OpenFile(const char* file_name) { model->OpenFile(file_name); }
void Controller::OtherMethods(Coordinates& data) { model->OtherMethods(data); }
void Controller::AffineRotate(Coordinates& data) { model->AffineRotate(data); }

std::vector<unsigned int>& Controller::get_polygons() noexcept {
  return model->get_polygons();
}
std::vector<float>& Controller::get_vertexes() noexcept {
  return model->get_vertexes();
}
std::vector<unsigned int> Controller::get_polygons() const noexcept {
  return model->get_polygons();
}
std::vector<float> Controller::get_vertexes() const noexcept {
  return model->get_vertexes();
}
size_t Controller::GetQuantityFaces() const noexcept {
  return model->GetQuantityFaces();
}

size_t Controller::GetQuantityVertexes() const noexcept {
  return model->GetQuantityVertexes();
}

void Controller::AutosaveWriting(s21::Autosave data) {
  model->AutosaveWriting(data);
}

void Controller::AutoSaveReading(s21::Autosave& data) {
  model->AutosaveReading(data);
}

}  // namespace s21
