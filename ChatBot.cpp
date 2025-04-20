#include "chat.h"
#include "message.h"
#include "messageContent.h"
#include "messageContentStruct.h"
#include "user.h"
#include <iostream>
#include <memory>

int main() {

  User user1("Yan", "Yan2201", "12345");
  User user2("Elena", "Ek", "12345");
  User user3("Sergei", "Sg", "12345");
  user1.showUserData();
  user2.showUserData();
  user3.showUserData();

  // проверка системы сообщений
  // создаем умный указатель на отправителя - user1
  std::shared_ptr<User> user1_ptr = std::make_shared<User>(user1);
  std::shared_ptr<User> user2_ptr = std::make_shared<User>(user2);
  std::shared_ptr<User> user3_ptr = std::make_shared<User>(user3);

  // создаем вектор умных указателей на получателей - user2 и user3
  std::vector<std::shared_ptr<User>> recipients;
  recipients.push_back(user2_ptr);
  recipients.push_back(user3_ptr);

  // задаем текст сообщения через переменную
  std::string text_tmp = "Тестовое сообщение";

  // создаем объект структуры под тип текст
  TextContent textContent(text_tmp); // создали структуру
  MessageContent<TextContent> iMessageContentText(
      textContent); // создали объект содержания сообщения с текстом
  std::shared_ptr<IMessageContent> iMessageContentText_ptr =
      std::make_shared<MessageContent<TextContent>>(textContent);

  // задаем картинку через переменную
  std::string image_tmp = "Тестовая картинка";

  // создаем объект структуры под тип картинка
  ImageContent imageContent(image_tmp);
  MessageContent<ImageContent> iMessageContentImage(imageContent);
  std::shared_ptr<IMessageContent> iMessageContentImage_ptr =
      std::make_shared<MessageContent<ImageContent>>(imageContent);

  // создаем vector из messageContent, который содержит сообщение состоящее из
  // текста и картинки
  std::vector<std::shared_ptr<IMessageContent>> messageContent;
  messageContent.push_back(iMessageContentText_ptr);
  messageContent.push_back(iMessageContentImage_ptr);

  // теперь создаём объект Message, который, в свою очередь, дальше будет
  // включен в класс Chat
  Message message1(messageContent, user1_ptr, recipients);

  std::cout << std::endl;
  return 0;
}