#pragma once
#include "user/user.h"
#include <memory>
#include <string>
#include <vector>

struct InitDataArray {
  std::string _messageText;                       ///< Текст сообщения
  std::string _timeStamp;                         ///< Временная метка сообщения
  std::shared_ptr<User> _sender;                  ///< Отправитель сообщения
  std::vector<std::shared_ptr<User>> _recipients; ///< Список получателей сообщения

  InitDataArray(std::string messageText, std::string timeStamp, std::shared_ptr<User> sender,
                std::vector<std::shared_ptr<User>> _recipients);

  /// @brief Деструктор по умолчанию.
  virtual ~InitDataArray() = default;
};

// structs for different types of content in one message
struct TextContent {
  std::string _text;

  TextContent(const std::string &text) : _text(text) {};
  ~TextContent() = default;
};

struct FileContent { // will be realized further
  std::string _fileName;

  FileContent(const std::string &fileName) : _fileName(fileName) {};
  ~FileContent() = default;
};
struct ImageContent { // will be realized further
  std::string _image;

  ImageContent(const std::string &image) : _image(image) {};
  ~ImageContent() = default;
};