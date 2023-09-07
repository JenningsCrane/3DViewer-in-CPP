#include "controller.h"

void Controller::Rotation(coordinates &data) { model->AffineRotate(data); }
void Controller::SubMethods(coordinates &data) { model->OtherMethods(data); }

void Controller::writing_data(info &data) {
  model->parser->ProcessingFile::WriteFileProcess(data);
}

void Controller::read_file(info &data) {
  model->parser->ProcessingFile::ReadFileProcess(data);
}
