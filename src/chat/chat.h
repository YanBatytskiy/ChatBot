#pragma once

#include "message/message.h"
#include "user/user.h"
#include <memory>
#include <vector>

struct Participant {
  std::weak_ptr<User> _user;
  std::size_t _lastReadMessageIndex;
};

class Chat {
private:
  std::vector<Participant> _participants;
  std::vector<std::shared_ptr<Message>> _messages;

public:
  Chat() = default;
  // constructor for an empty chat. not initilize_messagess becouse
  // constructor of vector will make it empty automatically

  virtual ~Chat() = default; // destructor

  // add participant to structure
  void addParticipant(const std::shared_ptr<User> &user);

  // add message to chat
  void addMessage(const std::shared_ptr<Message> &message);

  // get message from chat
  const std::vector<std::shared_ptr<Message>> &getMessages() const;

  // get participants of the chat
  const std::vector<Participant> &getParticipants() const;

  // get LastReadMessageIndex of the chat for participant
  std::size_t getLastReadMessageIndex(const std::shared_ptr<User> &user) const;

  // print full chat
  void printChat(const std::shared_ptr<User> &currentUser);

  // remove Participant from chat
  void removeParticipant(const std::shared_ptr<User> &user);

  void updateLastReadMessageIndex(const std::shared_ptr<User> &user, std::size_t newLastReadMessageIndex);

  /**
   * @brief Отметить все сообщения во всех чатах как прочитанные.
   */
  void makeAllRead();
};