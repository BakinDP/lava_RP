#include <filesystem>
#include <iostream>
#include <sys\\stat.h>

#define templatesAmount 3

using namespace std;

string getCurrentPath() { //    Получить путь исполняемого файла; ожидается
                          //    корневая папка набора
  filesystem::path bufferPath = filesystem::current_path();
  string path = bufferPath.generic_string();
  return path;
}

bool doesFileExist(
    string &name) { //   Проверить существование файла в текущей папке
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}

string findFirstPng() { //  Найти первую картинку в текущей папке
  string path = getCurrentPath();
  string ext = ".png";
  for (auto &p : filesystem::directory_iterator(path))
    if (p.path().extension() == ext && p.path().stem().string() != "pack") {
      return p.path().stem().string();
      break;
    }
  return "fileNotFound_doNotUseThisName"; //  Не использовать NULL, приводит к
                                          //  ошибке
}

bool doesTextureFileExist(
    string skinName) { // Проверить существование текстуры в \textures\item
  string path = getCurrentPath() + "\\assets\\minecraft\\textures\\item";
  for (auto &p : filesystem::directory_iterator(path)) {
    if (p.path().stem().string() + ".png" == skinName) {
      return true;
      break;
    }
  }
  return false;
}

bool doesTemplateExist(
    string templateName) { //    Проверить существование шаблонов
  string path =
      getCurrentPath() + "\\assets\\minecraft\\models\\item\\template";
  string ext = ".json";
  for (auto &p : filesystem::directory_iterator(path)) {
    if (p.path().extension() == ext &&
        p.path().stem().string() == templateName) {
      return true;
      break;
    }
  }
  return false;
}

void changeTemplateTexture(
    string skinName) { //    Изменить название текстуры в файле тотема после
                       //    копирования
  string COMMAND_CHANGE =
      "start powershell -Command \"(gc "
      "./assets/minecraft/models/item/totem_of_undying.json) -replace "
      "'template_texture', '" +
      skinName +
      "' | Out-File -encoding ASCII "
      "./assets/minecraft/models/item/totem_of_undying.json\"";
  system(COMMAND_CHANGE.c_str());
}

void loadMenu() { //  Меню загрузки тотема
  int variantLoad = -1;
  string skinName;

  do {
    system("cls");
    cout << "BBEDNTE HNK" << endl;

    cin >> skinName;
    skinName += ".png";
  } while (!doesTextureFileExist(skinName));

  while (variantLoad < 0 || variantLoad > 3) {
    system("cls");
    cout << "KAKON BAPNANT?" << endl;
    cout << "1 - Steve" << endl;
    cout << "2 - Alex" << endl;
    cout << "3 - Totem" << endl;
    cout << "-----------" << endl;
    cout << "4 - README" << endl;
    cout << "0 - BbIXOD" << endl;
    cout << "---------------" << endl << endl;

    cin >> variantLoad;

    string readmeFile = "README";
    if (variantLoad == 4 && doesFileExist(readmeFile)) {
      string readme = "notepad README";
      system(readme.c_str());
    }
  }

  switch (variantLoad) {
  case 0: {
    break;
  }
  case 1: { //  Скопировать шаблон Стива
    string COMMAND_COPY =
        "COPY /Y .\\assets\\minecraft\\models\\item\\template\\full.json "
        ".\\assets\\minecraft\\models\\item\\totem_of_undying.json";

    system(COMMAND_COPY.c_str());

    changeTemplateTexture(skinName);
    break;
  }
  case 2: { //  Скопировать шаблон Алекс
    string COMMAND_COPY =
        "COPY /Y .\\assets\\minecraft\\models\\item\\template\\slim.json "
        ".\\assets\\minecraft\\models\\item\\totem_of_undying.json";

    system(COMMAND_COPY.c_str());
    changeTemplateTexture(skinName);
    break;
  }
  case 3: { //  Скопировать шаблон простого тотема
    string COMMAND_COPY =
        "COPY /Y .\\assets\\minecraft\\models\\item\\template\\small.json "
        ".\\assets\\minecraft\\models\\item\\totem_of_undying.json";

    system(COMMAND_COPY.c_str());

    changeTemplateTexture(skinName);
    break;
  }
  }
  changeTemplateTexture(skinName);
}

void createMenu() { //  Меню создания тотема
  int variantCreate = -1;

  while (variantCreate < 0 || variantCreate > 3) {
    system("cls");
    cout << "4TO XOTNTE CO3DAT?" << endl;
    cout << "1 - Steve" << endl;
    cout << "2 - Alex" << endl;
    cout << "3 - Totem" << endl;
    cout << "-----------" << endl;
    cout << "4 - README" << endl;
    cout << "0 - BbIXOD" << endl;
    cout << "---------------" << endl << endl;

    cin >> variantCreate;

    string readmeFile = "README";
    if (variantCreate == 4 && doesFileExist(readmeFile)) {
      string readme = "notepad README";
      system(readme.c_str());
    }
  }

  string skinName;

  system("cls");
  cout << "BBEDNTE HNK" << endl;

  cin >> skinName;
  skinName += ".png";

  if (doesFileExist(skinName)) { // Найти в корневой папке файл с названием,
                                 // совпадающим с ником
    string COMMAND_MOVE =
        "MOVE /Y " + skinName + " .\\assets\\minecraft\\textures\\item";
    system(COMMAND_MOVE.c_str());
  } else if (findFirstPng() !=
             "fileNotFound_doNotUseThisName") { //    Если файл из прошлого
                                                //    пункта не найден, выбрать
                                                //    первый попавшийся за
                                                //    исключением pack.png
    string bufferName = findFirstPng() + ".png";
    string COMMAND_REN = "RENAME " + bufferName + " " + skinName;
    string COMMAND_MOVE =
        "MOVE /Y " + skinName + " .\\assets\\minecraft\\textures\\item";

    system(COMMAND_REN.c_str());
    system(COMMAND_MOVE.c_str());
  } else if (findFirstPng() ==
             "fileNotFound_doNotUseThisName") { //    Алгоритм не нашел ни
                                                //    одного подходящего файла
    cout << "HE HANDEHO .png" << endl;
    variantCreate = 0;
    system("pause");
  } else { //   Ошибка, возникающая лишь в самых непредвиденных обстоятельствах
    cout << "THIS MESSAGE SHOULD NEVER APPEAR (reach me out in Lava discord - "
            "@buildanation)"
         << endl;
    variantCreate = 0;
    system("pause");
  }

  switch (variantCreate) {
  case 0: {
    break;
  }
  case 1: { //  Скопировать шаблон Стива
    string COMMAND_COPY =
        "COPY /Y .\\assets\\minecraft\\models\\item\\template\\full.json "
        ".\\assets\\minecraft\\models\\item\\totem_of_undying.json";

    system(COMMAND_COPY.c_str());

    changeTemplateTexture(skinName);
    break;
  }
  case 2: { //  Скопировать шаблон Алекс
    string COMMAND_COPY =
        "COPY /Y .\\assets\\minecraft\\models\\item\\template\\slim.json "
        ".\\assets\\minecraft\\models\\item\\totem_of_undying.json";

    system(COMMAND_COPY.c_str());
    changeTemplateTexture(skinName);
    break;
  }
  case 3: { //  Скопировать шаблон простого тотема
    string COMMAND_COPY =
        "COPY /Y .\\assets\\minecraft\\models\\item\\template\\small.json "
        ".\\assets\\minecraft\\models\\item\\totem_of_undying.json";

    system(COMMAND_COPY.c_str());

    changeTemplateTexture(skinName);
    break;
  }
  }
}

void welcomeMenu() {
  int variant = -1;

  while (variant < 0 || variant > 2) {
    system("cls");
    cout << "XOTNTE CO3DAT NJlN 3ArPY3NT?" << endl;
    cout << "1 - 3ArPY3NT" << endl;
    cout << "2 - CO3DAT" << endl;
    cout << "-----------" << endl;
    cout << "3 - README" << endl;
    cout << "0 - BbIXOD" << endl;
    cout << "---------------" << endl << endl;

    cin >> variant;

    string readmeFile = "README";
    if (variant == 3 && doesFileExist(readmeFile)) {
      string readme = "notepad README";
      system(readme.c_str());
    }
  }

  switch (variant) {
  case 0:
    break;
  case 1:
    loadMenu();
    break;
  case 2:
    createMenu();
    break;
  }
}

int main() {
  string templateList[templatesAmount] = {"full", "slim",
                                          "small"}; //  Набор всех шаблонов
  bool flag = true;
  for (int i = 0; i < templatesAmount;
       i++) //  Проверка на наличие всех шаблонов
    if (!doesTemplateExist(templateList[i]))
      flag = false;

  if (flag)
    welcomeMenu();
  else {
    filesystem::path bufferPath = filesystem::current_path();
    string path = bufferPath.generic_string() +
                  "\\assets\\minecraft\\models\\item\\template";
    cout << "SOME TEMPLATES ARE MISSING, RETURN THEM BACK TO " + path +
                " IN ORDER TO CONTINUE"
         << endl;
    system("pause");
  }

  return 0;
}
