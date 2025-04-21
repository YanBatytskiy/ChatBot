#include "user_chat_list.h"
#include "user.h"
#include <memory>

// constructors
UserChatList::UserChatList(const std::shared_ptr<User> &owner)
    : _owner(owner) {};

// getters
std::shared_ptr<User> UserChatList::getOwner() const { return _owner; }

std::vector<std::shared_ptr<Chat>> UserChatList::getChatsList() const {
  return _chatsList;
}
std::vector<std::size_t> UserChatList::getLastIndexRead() const {
  return _lastReadIndex;
}

// setters
void UserChatList::addChat(const std::shared_ptr<Chat> &chat) {
  _chatsList.push_back(chat);
  _lastReadIndex.push_back(0);
}

// additional methods
void UserChatList::makeAllRead() {} // make all uread messages as read;