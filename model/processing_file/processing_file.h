#ifndef PROCESSING_FILE_H
#define PROCESSING_FILE_H

#include "open_file.h"
#include "read_file.h"
#include "wrirting_data.h"

class ProcessingFile {
 public:
  void ReadFileProcess(info &data) {
    oFile.Open(data);
    rFile.Read(data);
  }
  void WriteFileProcess(info &data) {
    oFile.Open(data);
    wFile.Write(data);
  }

 private:
  ReadFile rFile;
  WritingData wFile;
  OpenFile oFile;
};

#endif  // PROCESSING_FILE_H
