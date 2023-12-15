#include "open_file.h"

#include <fstream>

namespace s21 {

std::ifstream& OpenFile::Open(const std::string file_name) {
  file_name_ = file_name;
  OpenFileStream();
  return get_stream();
}

std::ifstream& OpenFile::Open(const char* file_name) {
  file_name_ = file_name;
  OpenFileStream();
  return get_stream();
}

std::ifstream& OpenFile::get_stream() { return file_stream_; }

std::string OpenFile::get_file_name() const noexcept { return file_name_; }

void OpenFile::OpenFileStream() {
  if (file_stream_.is_open()) {
    file_stream_.close();  // Закрыть поток, если он уже открыт.
  }
  file_stream_.open(file_name_);
  if (!file_stream_.is_open()) {  // auto close
    throw std::ios_base::failure("No such file" + file_name_);
  }
}

}  // namespace s21