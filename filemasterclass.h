#ifndef FILEMASTERCLASS_H
#define FILEMASTERCLASS_H
#include <string>

class fileMasterClass {
public:
  fileMasterClass();

  std::string *getCurrentPath();
  std::string findFirstPng();

  bool doesTextureFileExist(std::string skinName);
  bool doesFileExist(std::string &name);
  bool doesTemplateExist(std::string templateName);

  void createNewTotem(std::string skinName);
  void exportTemplate(std::string templateName, std::string skinName);

private:
  std::string currentPath; //  Путь корневой папки
  void changeTemplateTexture(std::string skinName);
};

#endif // FILEMASTERCLASS_H
