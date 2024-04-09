#include "filemasterclass.h"
#include <filesystem>
#include <fstream>
#include <sys\\stat.h>

//  Получить путь исполняемого файла; ожидается корневая папка набора
std::string *fileMasterClass::getCurrentPath() { return &currentPath; }

// Проверить существование файла в корневой папке
bool fileMasterClass::doesFileExist(std::string &name) {
  struct stat buffer;

  return (stat(name.c_str(), &buffer) == 0);
}

//  Найти первую картинку в корневой папке
std::string fileMasterClass::findFirstPng() {
  std::string path = currentPath;
  std::string ext = ".png";
  for (auto &p : std::filesystem::directory_iterator(path))
    if (p.path().extension() == ext && p.path().stem().string() != "pack") {
      return p.path().stem().string();
      break;
    }

  return "";
}

//  Проверить существование текстуры в /textures/item
bool fileMasterClass::doesTextureFileExist(std::string skinName) {
  std::string path = currentPath + "/assets/minecraft/textures/item";
  for (auto &p : std::filesystem::directory_iterator(path)) {
    if (p.path().stem().string() + ".png" == skinName) {
      return true;
      break;
    }
  }

  return false;
}

//  Проверить существование шаблона
bool fileMasterClass::doesTemplateExist(std::string templateName) {
  std::string path = currentPath + "/assets/minecraft/models/item/template";
  std::string ext = ".json";
  for (auto &p : std::filesystem::directory_iterator(path)) {
    if (p.path().extension() == ext &&
        p.path().stem().string() == templateName) {
      return true;
      break;
    }
  }

  return false;
}

//  Создание тотема
void fileMasterClass::createNewTotem(std::string skinName) {
  std::string firstPng = findFirstPng();

  if (doesFileExist(skinName)) {
    std::string sourcePath = currentPath + "/" + skinName;
    std::string destPath =
        currentPath + "/assets/minecraft/textures/item/" + skinName;

    std::filesystem::copy(sourcePath, destPath,
                          std::filesystem::copy_options::overwrite_existing);
  } else if (!firstPng.empty()) {
    std::string sourcePath = currentPath + "/" + firstPng + ".png";
    std::string destPath =
        currentPath + "/assets/minecraft/textures/item/" + skinName;

    std::filesystem::rename(sourcePath, destPath);
  }
}

//  Открыть файл в потоке
std::string getFile(std::ifstream &is) {
  std::string contents;
  for (char ch; is.get(ch); contents.push_back(ch)) {
  }

  return contents;
}

//  Заменить все подстроки в строке
void findReplace(std::string &file_contents, const std::string &morn,
                 const std::string &night) {
  auto pos = file_contents.find(morn);
  while (pos != std::string::npos) {
    file_contents.replace(pos, morn.length(), night);
    pos = file_contents.find(morn, pos);
  }
}

//  Изменить название текстуры в файле тотема после экспорта
void fileMasterClass::changeTemplateTexture(std::string skinName) {
  std::string totemInPath =
      currentPath + "/assets/minecraft/models/item/temp_template.json";
  std::string totemOutPath =
      currentPath + "/assets/minecraft/models/item/totem_of_undying.json";
  std::ifstream inputFile(totemInPath);
  std::ofstream outputFile(totemOutPath);

  std::string contents = getFile(inputFile);
  findReplace(contents, "template_texture", skinName);
  outputFile << contents;

  inputFile.close();
  outputFile.close();
  std::remove(totemInPath.c_str());
}

//  Экспорт шаблона
void fileMasterClass::exportTemplate(std::string templateName,
                                     std::string skinName) {
  std::string sourcePath = currentPath +
                           "/assets/minecraft/models/item/template/" +
                           templateName + ".json";
  std::string destPath =
      currentPath + "/assets/minecraft/models/item/temp_template.json";
  std::filesystem::copy(sourcePath, destPath,
                        std::filesystem::copy_options::overwrite_existing);

  changeTemplateTexture(skinName);
}

fileMasterClass::fileMasterClass() {
  std::filesystem::path bufferPath = std::filesystem::current_path();
  currentPath = bufferPath.generic_string();
}
