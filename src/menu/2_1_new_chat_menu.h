#pragma once
#include "system/chat_system.h"
#include "system/system_function.h"

void LoginMenu_1NewChatMakeParticipants(ChatSystem &chatSystem, std::shared_ptr<Chat> &chat,
                                        std::size_t activeUserIndex,
                                        MessageTarget target); // создение нового сообщения путем выбора пользователей

void CreateAndSendNewChat(ChatSystem &chatSystem, std::size_t activeUserIndex,
                          bool sendToAll); // общая функция для отправки сообщения в новый чат тремя способами

void LoginMenu_1NewChat(ChatSystem &chatSystem); // создание нового сообщения