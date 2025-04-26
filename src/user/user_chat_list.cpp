#include "user/user_chat_list.h"
#include "user/user.h"

// constructors
UserChatList::UserChatList(const std::shared_ptr<User> &owner) : _owner(owner) {};

// getters

std::size_t UserChatList::getChatCount() const { return _chatCount; };

std::weak_ptr<User> UserChatList::getOwner() const { return _owner; }

std::vector<std::weak_ptr<Chat>> UserChatList::getChatFromList() const { return _chatList; }
std::vector<std::size_t> UserChatList::getLastReadIndex() const { return _lastReadIndex; }

// setters
void UserChatList::setChatCount(std::size_t chatCount) { _chatCount = chatCount; };

void UserChatList::addChat(const std::weak_ptr<Chat> &chat) {
  _chatList.push_back(chat);
  _lastReadIndex.push_back(0);
  ++_chatCount;
}

void UserChatList::setLastReadIndex(std::size_t index, std::size_t value) {
  _lastReadIndex.insert(_lastReadIndex.begin() + index, value);
}

// additional methods
void UserChatList::makeAllRead() {} // make all uread messages as read;