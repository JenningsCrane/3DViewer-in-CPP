#ifndef CPP4_3DVIEWER_V2_0_1_MODEL_PROCESSING_FILE_OPEN_FILE_H_
#define CPP4_3DVIEWER_V2_0_1_MODEL_PROCESSING_FILE_OPEN_FILE_H_

#include <fstream>
#include <string>

namespace s21 {

class OpenFile {
 public:
  OpenFile() = default;
  OpenFile(const OpenFile& other);
  OpenFile(OpenFile&& other) = default;
  ~OpenFile() = default;

  OpenFile& operator=(const OpenFile& other);
  OpenFile& operator=(OpenFile&& ohter) = default;

  std::ifstream& Open(const std::string file_name);
  std::ifstream& Open(const char* file_name);
  std::ifstream& get_stream();
  std::string get_file_name() const noexcept;
  // void Close();

 private:
  std::string file_name_;
  std::ifstream file_stream_;

  void OpenFileStream();
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_MODEL_PROCESSING_FILE_OPEN_FILE_H_
