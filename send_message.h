#pragma once

class ISendMessage {
public:
  virtual ~ISendMessage() = default;
  virtual void send() = 0;
};

// send to one user
class SendToOne : public ISendMessage {};

// send to several users
class SendToSeveral : public ISendMessage {};

// send to all users
class SendToAll : public ISendMessage {};
