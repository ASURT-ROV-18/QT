#include <QApplication>
#include "copilotscreen.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  CoPilotScreen MainScreen;
  MainScreen.show();

  return a.exec();
}
