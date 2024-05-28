#pragma once
#include"inc.h"
class noncopyable
{
 public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

 protected:
  noncopyable() = default;
  ~noncopyable() = default;
};


class Poller : public noncopyable
{
    public:
        Poller(int s): m_socket(s){

        }
        ~Poller();
        void Update();
    private:
        int m_socket = -1;  
};
