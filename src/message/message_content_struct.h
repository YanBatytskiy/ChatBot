#pragma once
#include <string>

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