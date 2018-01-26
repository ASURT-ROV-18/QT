#include "copilotscreen.h"
#include "imageprocessingscreen.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  CoPilotScreen MainScreen;
  ImageProcessingScreen ipscreen;
  MainScreen.show();
  ipscreen.show();

  return a.exec();
}
