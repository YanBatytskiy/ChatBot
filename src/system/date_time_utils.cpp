#include "date_time_utils.h"
#include <ctime>

std::string getCurrentDateTime() { // вернет строку с текущей датой и временем

  time_t mytime = time(NULL);
  struct tm *now = localtime(&mytime);

  char date_stamp[20];
  char time_stamp[20];

  std::strftime(date_stamp, sizeof(date_stamp), "%Y-%m-%d", now);
  std::strftime(time_stamp, sizeof(time_stamp), "%H:%M:%S", now);

  return std::string(date_stamp) + ", " + time_stamp;
}