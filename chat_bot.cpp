#include "chat.h"
#include "message.h"
#include "message_content.h"
#include "message_content_struct.h"
#include "user.h"
#include "user_chat_list.h"
#include <iostream>
#include <memory>
#include <vector>

int main() {
  User user1("Yan", "Yan2201", "12345");
  User user2("Elena", "Ek", "12345");
  User user3("Sergei", "Sg", "12345");
  user1.showUserData();
  user2.showUserData();
  user3.showUserData();

  // проверка системы сообщений
  // создаем умный указатель на пользователей
  std::shared_ptr<User> user1_ptr = std::make_shared<User>(user1);
  std::shared_ptr<User> user2_ptr = std::make_shared<User>(user2);
  std::shared_ptr<User> user3_ptr = std::make_shared<User>(user3);

  // создаем вектор умных указателей на получателей - user2 и user3
  std::vector<std::shared_ptr<User>> recipients;
  recipients.push_back(user2_ptr);
  recipients.push_back(user3_ptr);

  // создаем список чатов UserChatList для каждого пользователя. Мы создвем и
  // привязываем список чатов при регистрации пользователя
  UserChatList user1_ChatsList(user1_ptr);
  UserChatList user2_ChatsList(user2_ptr);
  UserChatList user3_ChatsList(user3_ptr);

  std::shared_ptr<UserChatList> user1_ChatsList_ptr =
      std::make_shared<UserChatList>(user1_ChatsList);
  std::shared_ptr<UserChatList> user2_ChatsList_ptr =
      std::make_shared<UserChatList>(user1_ChatsList);
  std::shared_ptr<UserChatList> user3_ChatsList_ptr =
      std::make_shared<UserChatList>(user1_ChatsList);

  // привязываем список чатов к юзеру
  user1.initChats(user1_ChatsList_ptr);
  user1.initChats(user2_ChatsList_ptr);
  user1.initChats(user3_ChatsList_ptr);

  // создаем вектор участников чата и добавляем туда
  // отправителя, затем получателей
  std::vector<std::shared_ptr<User>> participients;
  participients.insert(participients.end(), recipients.begin(),
                       recipients.end());

  // добавляем в список уастников чата активного пользователя
  participients.push_back(user1_ptr);

  // создаем пустой чат с участниками
  // это тот чат, в котором мы пишем сообщение. Он либо новый либо был выбран
  // существующий
  Chat activeChat(participients);

  // qqq
  //  задаем текст сообщения через переменную
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
  std::shared_ptr<Message> message1_ptr = std::make_shared<Message>(message1);

  // добавляем сообщение в активный чат
  activeChat.addMessage(message1_ptr);
  std::shared_ptr<Chat> activeChat_ptr = std::make_shared<Chat>(activeChat);

  // добавляем новый чат в список чатов каждого пользователя
  user1.getUserChatList()->addChat(activeChat_ptr);

  std::cout << std::endl;
  return 0;
}