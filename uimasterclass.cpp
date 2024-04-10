#include "uimasterclass.h"
#include <filemasterclass.cpp>
#include <iostream>

#define maxAmountOfTemplates 32

using namespace std;

//  Проверить на наличие подходящих шаблонов
bool checkForJSONs() {
  std::filesystem::path bufferPath = std::filesystem::current_path();
  std::string currentPath = bufferPath.generic_string();
  std::string path = currentPath + "/assets/minecraft/models/item/template";
  std::string ext = ".json";
  for (auto &p : std::filesystem::directory_iterator(path))
    if (p.path().extension() == ext && p.path().stem().string() != "lava") {
      return true;
    }
  return false;
}

//  Загрузить шаблоны из /models/item/template в список и получить количество
//  загруженных шаблонов
int loadJSONs(string *list) {
  int iter = 0;

  std::filesystem::path bufferPath = std::filesystem::current_path();
  std::string currentPath = bufferPath.generic_string();
  std::string path = currentPath + "/assets/minecraft/models/item/template";
  std::string ext = ".json";
  for (auto &p : std::filesystem::directory_iterator(path))
    if (p.path().extension() == ext && iter < maxAmountOfTemplates &&
        p.path().stem().string() != "lava")
      *(list + (iter++)) = p.path().stem().string();

  return iter;
}

void loadMenu() { //  Меню загрузки тотема
  fileMasterClass *fileMaster =
      new fileMasterClass(); //  Экземпляр файлового мастера
  string variantLoad; //  Выбранный пользователем пункт списка
  string skinName; //  Имя игрока; соответствует названию текстуры
  string templatesList[maxAmountOfTemplates]; //  Список шаблонов
  bool killSwitch = false; //  При выходе убить оставшиеся процессы

  int templatesAmount =
      loadJSONs(templatesList); // Заполнить список имеющихся шаблонов

  while (atoll(variantLoad.c_str()) < 1 ||
         atoll(variantLoad.c_str()) > templatesAmount) {
    int iter = 0;
    system("cls");
    cout << "KAKON BAPNAHT?" << endl;
    while (iter < templatesAmount) {
      cout << iter + 1 << " - " << templatesList[iter] << endl;
      iter++;
    }
    cout << "-----------" << endl;
    cout << "R - README" << endl;
    cout << "E - BbIXOD" << endl;
    cout << "---------------" << endl << endl;

    cin >> variantLoad;

    string readmeFile = "README";
    if (variantLoad == "R" && fileMaster->doesFileExist(readmeFile)) {
      string readme = "notepad README";
      system(readme.c_str());
    } else if (variantLoad == "E") {
      killSwitch = true;
      break;
    }
  }

  if (!killSwitch) {
    do {
      system("cls");
      cout << "BBEDNTE HNK" << endl;

      cin >> skinName;
      skinName += ".png";
    } while (!fileMaster->doesTextureFileExist(skinName));

    fileMaster->exportTemplate(templatesList[atoll(variantLoad.c_str()) - 1],
                               skinName);
    system("cls");
    cout << "CPAbOTAJIO!" << endl;
    system("pause");
  }

  delete fileMaster;
}

void createMenu() { //  Меню создания тотема
  fileMasterClass *fileMaster =
      new fileMasterClass(); //  Экземпляр файлового мастера
  string variantCreate; //  Выбранный пользователем пункт списка
  string skinName; //  Имя игрока; соответствует названию текстуры
  string templatesList[maxAmountOfTemplates]; //  Список шаблонов
  bool killSwitch = false; //  При выходе убить оставшиеся процессы

  int templatesAmount =
      loadJSONs(templatesList); // Заполнить список имеющихся шаблонов

  while (atoll(variantCreate.c_str()) < 1 || atoll(variantCreate.c_str()) > 3) {
    int iter = 0;
    system("cls");
    cout << "4TO XOTNTE CO3DAT?" << endl;
    while (iter < templatesAmount) {
      cout << iter + 1 << " - " << templatesList[iter] << endl;
      iter++;
    }
    cout << "-----------" << endl;
    cout << "R - README" << endl;
    cout << "E - BbIXOD" << endl;
    cout << "---------------" << endl << endl;

    cin >> variantCreate;

    string readmeFile = "README";
    if (variantCreate == "R" && fileMaster->doesFileExist(readmeFile)) {
      string readme = "notepad README";
      system(readme.c_str());
    } else if (variantCreate == "E") {
      killSwitch = true;
      break;
    }
  }

  int correctInput = true; //  Проверка на корректность ввода (не pack)

  if (!killSwitch) {
    do {
      system("cls");
      cout << "BBEDNTE HNK";
      if (fileMaster->findFirstPng().empty())
        cout << " ( ! HE HANDEHbI .png ! )";
      cout << endl;

      cin >> skinName;

      correctInput = !fileMaster->findFirstPng().empty();
      if (skinName == "pack")
        correctInput = false;
      skinName += ".png";
    } while (!correctInput);

    fileMaster->createNewTotem(skinName);
    fileMaster->exportTemplate(templatesList[atoll(variantCreate.c_str()) - 1],
                               skinName);
    system("cls");
    cout << "CPAbOTAJIO!" << endl;
    system("pause");
  }
}

void uiMasterClass::welcomeMenu() {
  if (checkForJSONs()) {
    fileMasterClass *fileMaster =
        new fileMasterClass(); //  Экземпляр файлового мастера
    std::string variant = "0";
    bool killSwitch = false; //  При выходе убить оставшиеся процессы

    while (atoll(variant.c_str()) < 1 || atoll(variant.c_str()) > 2) {
      system("cls");
      cout << "XOTNTE CO3DAT NJlN 3ArPY3NT?" << endl;
      cout << "1 - 3ArPY3NT" << endl;
      cout << "2 - CO3DAT" << endl;
      cout << "-----------" << endl;
      cout << "R - README" << endl;
      cout << "E - BbIXOD" << endl;
      cout << "---------------" << endl << endl;

      std::cin >> variant;

      string readmeFile = "README";
      if (variant == "R" && fileMaster->doesFileExist(readmeFile)) {
        string readme = "notepad README";
        system(readme.c_str());
      } else if (variant == "E") {
        killSwitch = true;
        break;
      }
    }

    if (!killSwitch)
      switch (atoll(variant.c_str())) {
      case 1:
        loadMenu();
        break;
      case 2:
        createMenu();
        break;
      }
  } else {
    system("cls");
    cout << "HE HANDEHbI IIIAbJIONbI!" << endl;
    system("pause");
  }
}

uiMasterClass::uiMasterClass() {}
