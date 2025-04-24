#include "code_init_system.h"
#include "chat.h"
#include "message.h"
#include "message_content.h"
#include "message_content_struct.h"
#include "user.h"
#include "user_chat_list.h"

#include <memory>
#include <vector>

void systemInintTest(ChatSystem &_chatsystem) {

  // проверка системы сообщений
  // создаем умный указатель на пользователей
  auto user1_ptr = std::make_shared<User>("Alex2104", "Sasha", "12345");
  auto user2_ptr = std::make_shared<User>("Elena1510", "Elena", "12345");
  auto user3_ptr = std::make_shared<User>("Serg0101", "Sergei", "12345");
  user1_ptr->showUserData();
  user2_ptr->showUserData();
  user3_ptr->showUserData();

  auto activeUser_ptr = user1_ptr; // назначаем юзера, который сейчас в системе

  // добавляем пользователей в систему
  _chatsystem.addUser(user1_ptr);
  _chatsystem.addUser(user2_ptr);
  _chatsystem.addUser(user3_ptr);

  // создаем список чатов UserChatList для каждого пользователя. Мы создвем и
  // привязываем список чатов при регистрации пользователя
  std::shared_ptr<UserChatList> user1_ChatList_ptr =
      std::make_shared<UserChatList>(user1_ptr);
  std::shared_ptr<UserChatList> user2_ChatList_ptr =
      std::make_shared<UserChatList>(user2_ptr);
  std::shared_ptr<UserChatList> user3_ChatList_ptr =
      std::make_shared<UserChatList>(user3_ptr);

  // привязываем список чатов к юзеру
  user1_ptr->createChatList(user1_ChatList_ptr);
  user2_ptr->createChatList(user2_ChatList_ptr);
  user3_ptr->createChatList(user3_ChatList_ptr);

  // создаем вектор слабых умных указателей на получателей - user2 и user3 для
  // формирования сообщения
  std::vector<std::weak_ptr<User>> recipients;
  recipients.push_back(user2_ptr);
  recipients.push_back(user3_ptr);

  // создаем вектор участников чата и добавляем туда
  // отправителя, затем получателей
  std::vector<std::weak_ptr<User>> ActiveChatParticipients;
  ActiveChatParticipients.insert(ActiveChatParticipients.end(),
                                 recipients.begin(), recipients.end());

  // добавляем в список уастников чата активного пользователя
  ActiveChatParticipients.push_back(user1_ptr);

  // создаем пустой чат с участниками
  // это тот чат, в котором мы пишем сообщение. Он либо новый либо был выбран
  // существующий

  auto activeChat_ptr = std::make_shared<Chat>(
      ActiveChatParticipients); // это аналог двух операций но без
                                // дополнительной

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
  Message message1(messageContent, user1_ptr);
  std::shared_ptr<Message> message1_ptr = std::make_shared<Message>(message1);
  Message message2(messageContent, user2_ptr);
  std::shared_ptr<Message> message2_ptr = std::make_shared<Message>(message2);

  // добавляем сообщение в активный чат
  activeChat_ptr->addMessage(message1_ptr);
  activeChat_ptr->addMessage(message2_ptr);

  // добавляем новый чат в список чатов каждого пользователя
  user1_ptr->getUserChatList()->addChat(activeChat_ptr);
  user2_ptr->getUserChatList()->addChat(activeChat_ptr);
  user3_ptr->getUserChatList()->addChat(activeChat_ptr);

  //   message1_ptr->printMessage(activeUser_ptr);
  //   activeChat_ptr->printChat(activeUser_ptr);
};