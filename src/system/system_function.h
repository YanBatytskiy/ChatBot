#pragma once
#include "message/message_content_struct.h"
#include "system/chat_system.h"
#include <alloca.h>
#include <string>

enum class MessageTarget {One, Several, All};

int parseGetlineToInt(const std::string &str); // конвертация из string в int

std::size_t parseGetlineToSizeT(const std::string &str); // конвертация из string в size_t

void changeLastReadIndexForSender(const std::shared_ptr<User> &user, const std::shared_ptr<Chat> &chat);

void addMessageToChat(const InitDataArray &initDataArray, std::shared_ptr<Chat> &chat);

bool inputNewMessage(ChatSystem &chatSystem, std::shared_ptr<Chat> chat);

std::string TextToLower(const std::string &str); // приведение к нижнему регистру