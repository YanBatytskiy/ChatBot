#include "chat/chat.h"
#include <algorithm>
#include <iostream>
// #include <iterator>

// Chat::Chat(const std::vector<std::shared_ptr<User>>
//                &participients) { // constructor for an empty chat. not initilize_messagess becouse
//   // constructor of vector will make it empty automatically
//   for (const auto &user : participients) {
// }
// };

// add participient to structure
void Chat::addParticipient(const std::shared_ptr<User> &user) {
  Participient participient;
  participient._user = user;
  participient._lastReadMessageIndex = 0;
  _participients.push_back(participient);
}

// add message to chat
void Chat::addMessage(const std::shared_ptr<Message> &message) { _messages.push_back(message); }

// get message from chat
const std::vector<std::shared_ptr<Message>> &Chat::getMessages() const { return _messages; }

// get participients of the chat
const std::vector<Participient> &Chat::getParticipients() const { return _participients; }

// get LastReadMessageIndex of the chat for participient
std::size_t Chat::getLastReadMessageIndex(const std::shared_ptr<User> &user) const {

  const auto &participients = _participients;
  auto it = std::find_if(participients.begin(), participients.end(), [&user](const Participient &participient) {
    auto user_ptr = participient._user.lock();
    return user_ptr && (user_ptr == user);
  });
  if (it != participients.end()) {
    return it->_lastReadMessageIndex;
  } else {
    std::cerr << "[Ошибка] Пользователь не найден среди участников чата." << std::endl;
    return 0;
  }
}

// print full chat
void Chat::printChat(const std::shared_ptr<User> &currentUser) {
  if (!_messages.empty()) {
    for (const auto &message : _messages) {
      message->printMessage(currentUser);
    }
  } else
    std::cout << "Cообщуний нет." << std::endl;
}

// remove Participient from chat
void Chat::removeParticipient(const std::shared_ptr<User> &user) {
  // ДОДЕЛАТЬ
};

void Chat::updateLastReadMessageIndex(const std::shared_ptr<User> &user, std::size_t newLastReadMessageIndex) {

  auto &participients = _participients; // взяли вектор участников чата
  auto it = std::find_if(participients.begin(), participients.end(), [&user](const Participient &partisipient) {
    auto user_ptr = partisipient._user.lock();

    return user_ptr && (user_ptr == user);
  });

  if (it != participients.end()) {
    it->_lastReadMessageIndex = newLastReadMessageIndex;
  } else {
    std::cerr << "[Ошибка] Пользователь не найден среди участников чата." << std::endl;
  }
};

/**
 * @brief Отметить все сообщения во всех чатах как прочитанные.
 */
void Chat::makeAllRead() {};
// ДОДЕЛАТЬ
