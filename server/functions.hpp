#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <condition_variable>
#include <iosfwd>
#include <mutex>

#include "buffer.hpp"

namespace functions
{
  std::string readFromInput();
  void handleNumString(std::string& str);

  void runFirstThread(
    std::shared_ptr< std::mutex >,
    std::shared_ptr< std::condition_variable >,
    std::shared_ptr< Buffer >,
    bool&
  );

  void runSecondThread(
    std::shared_ptr< std::mutex >,
    std::shared_ptr< std::condition_variable >,
    std::shared_ptr< Buffer >,
    bool &,
    int  &,
    int  &
  );
};

#endif
