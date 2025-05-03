#include "chat/chat.h"
#include "exception/validation_exception.h"
#include <algorithm>
#include <iostream>
// #include <iterator>

// Chat::Chat(const std::vector<std::shared_ptr<User>>
//                &participants) { // constructor for an empty chat. not initilize_messagess becouse
//   // constructor of vector will make it empty automatically
//   for (const auto &user : participants) {
// }
// };

// add participant to structure
void Chat::addParticipant(const std::shared_ptr<User> &user) {
  Participant participant;
  participant._user = user;
  participant._lastReadMessageIndex = 0;
  _participants.push_back(participant);
}

// add message to chat
void Chat::addMessage(const std::shared_ptr<Message> &message) { _messages.push_back(message); }

// get message from chat
const std::vector<std::shared_ptr<Message>> &Chat::getMessages() const { return _messages; }

// get participants of the chat
const std::vector<Participant> &Chat::getParticipants() const { return _participants; }

// get LastReadMessageIndex of the chat for participant
std::size_t Chat::getLastReadMessageIndex(const std::shared_ptr<User> &user) const {

  const auto &participants = _participants;
  auto it = std::find_if(participants.begin(), participants.end(), [&user](const Participant &participant) {
    auto user_ptr = participant._user.lock();
    return user_ptr && (user_ptr == user);
  });
  if (it != participants.end()) {
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

// remove Participant from chat
void Chat::removeParticipant(const std::shared_ptr<User> &user) {
  // ДОДЕЛАТЬ
}

void Chat::updateLastReadMessageIndex(const std::shared_ptr<User> &user, std::size_t newLastReadMessageIndex) {

  // нашли нужного пользователя
  auto it = std::find_if(_participants.begin(), _participants.end(), [&user](const Participant &partisipient) {
    auto user_ptr = partisipient._user.lock();

    return user_ptr && (user_ptr->getLogin() == user->getLogin());
  });
  try {
    if (it != _participants.end())
      it->_lastReadMessageIndex = newLastReadMessageIndex;
    else
      throw UserNotInListException(" updateLastReadMessageIndex");

  } catch (const ValidationException &ex) {
    std::cout << " ! " << ex.what() << std::endl;
  }
}