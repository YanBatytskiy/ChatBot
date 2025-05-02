#pragma once
#include "system/chat_system.h"
#include <string>

int parseGetlineToInt(const std::string &str); // конвертация из string в int

std::size_t parseGetlineToSizeT(const std::string &str); // конвертация из string в size_t

void inputNewMessage(ChatSystem &chatSystem, std::shared_ptr<Chat> chat, std::size_t unReadCountIndex);