#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cmath>

int main()
{
  int sock;
  struct sockaddr_in addr;

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if(sock < 0)
  {
    std::cerr << "error: socket\n";
    return 1;
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(5421);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);

  const int N = 3;

  while (true)
  {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
      std::cerr << "error: socket\n";
      return 1;
    }

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
      std::cout << "connection waiting...\n";
      close(sock);
      sleep(1);
      continue;
    }
    std::cout << "connected to program 1\n";

    while (true)
    {
      char data[N];
      int dataSize = recv(sock, data, N, 0);
      if (dataSize <= 0)
      {
        std::cerr << "error: data is not received\n";
        close(sock);
        break;
      }
      int sum = 0;
      for (int i = 0; i < dataSize; i++) {
        sum = sum * 10 + (data[i] - '0');
      }
      if ((dataSize > 2) && (sum % 32 == 0))
      {
        std::cout << "data received: sum = " << sum << '\n';
      }
      else
      {
        std::cerr << "error: received data is incorrect: sum = " << sum << "\n";
      }
    }
  }
}
