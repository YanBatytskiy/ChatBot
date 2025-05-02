#pragma once
#include "system/chat_system.h"

void loginMenu_2ChatList(ChatSystem &chatSystem);

void loginMenu_2EditChat(ChatSystem &chatSystem, const std::shared_ptr<Chat> &chat /*, std::size_t unReadCountIndex*/);
