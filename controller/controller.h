#ifndef CPP4_3DVIEWER_V2_0_1_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_1_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"
#include "../viewer_data.h"

namespace s21 {

class Controller {
 public:
  static Controller& getInstance(Model* m) {
    static Controller instance = Controller(m);
    return instance;
  }

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

  void AutosaveWriting(s21::Autosave model);
  void AutoSaveReading(s21::Autosave& model);

 private:
  Controller() = delete;
  Controller(Model* m) : model(m) {}
  Model* model;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_CONTROLLER_CONTROLLER_H_
