#pragma once

#include "message/message.h"
#include "user/user.h"
#include <memory>
#include <vector>

struct Participient {
  std::weak_ptr<User> _user;
  std::size_t _lastReadMessageIndex;
};

class Chat {
private:
  std::vector<Participient> _participients;
  std::vector<std::shared_ptr<Message>> _messages;

public:
  Chat() = default;
  // constructor for an empty chat. not initilize_messagess becouse
  // constructor of vector will make it empty automatically

  virtual ~Chat() = default; // destructor

  // add participient to structure
  void addParticipient(const std::shared_ptr<User> &user);

  // add message to chat
  void addMessage(const std::shared_ptr<Message> &message);

  // get message from chat
  const std::vector<std::shared_ptr<Message>> &getMessages() const;

  // get participients of the chat
  const std::vector<Participient> &getParticipients() const;

  // get LastReadMessageIndex of the chat for participient
  std::size_t getLastReadMessageIndex(const std::shared_ptr<User> &user) const;

  // print full chat
  void printChat(const std::shared_ptr<User> &currentUser);

  // remove Participient from chat
  void removeParticipient(const std::shared_ptr<User> &user);

  void updateLastReadMessageIndex(const std::shared_ptr<User> &user, std::size_t newLastReadMessageIndex);

  /**
   * @brief Отметить все сообщения во всех чатах как прочитанные.
   */
  void makeAllRead();
};