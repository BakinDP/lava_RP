#include <uimasterclass.cpp>

#define templatesAmount 3

int main() {
  uiMasterClass *uiMaster =
      new uiMasterClass(); //  Экземпляр интерфейсного мастера

  uiMaster->welcomeMenu();

  delete uiMaster;
  return 0;
}

  return 0;
}
