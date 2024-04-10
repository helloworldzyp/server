#include"inc.h"
#include"test.hpp"

void create_and_bind_socket(int& sock, int port) {
    // 创建 TCP 套接字
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Failed to create socket\n";
        exit(EXIT_FAILURE);
    }
    
    //设置 SO_REUSEPORT 选项
    int optval = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)) == -1) {
        std::cerr << "Failed to set SO_REUSEPORT option\n";
        close(sock);
        exit(EXIT_FAILURE);
    }
    
    // 绑定套接字到指定端口
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);
    if (bind(sock, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        std::cerr << "Failed to bind socket\n";
        close(sock);
        exit(EXIT_FAILURE);
    }
}

// int main() {
//     int socket1, socket2;
//     int port = 9999;
    
//     // 创建两个套接字并绑定到同一端口
//     create_and_bind_socket(socket1, port);
//     create_and_bind_socket(socket2, port);
    
//     // 开始监听连接
//     if (listen(socket1, 5) == -1 || listen(socket2, 5) == -1) {
//         std::cerr << "Failed to listen on socket\n";
//         close(socket1);
//         close(socket2);
//         exit(EXIT_FAILURE);
//     }
    
//     std::cout << "Sockets are listening on port " << port << "...\n";
    
//     try {
//         while (true) {
//             // 接受连接
//             struct sockaddr_in client_addr;
//             socklen_t client_len = sizeof(client_addr);
//             int conn1 = accept(socket1, reinterpret_cast<struct sockaddr*>(&client_addr), &client_len);
//             std::cout << "Accepted connection from: " << inet_ntoa(client_addr.sin_addr) << "\n";
            
//             int conn2 = accept(socket2, reinterpret_cast<struct sockaddr*>(&client_addr), &client_len);
//             std::cout << "Accepted  2 connection from: " << inet_ntoa(client_addr.sin_addr) << "\n";
            
//             // 在这里可以处理连接请求，例如处理数据或发送响应
            
//             // 关闭连接
//             close(conn1);
//             close(conn2);
//         }
//     } catch (...) {
//         std::cerr << "An exception occurred\n";
//     }
    
//     // 关闭套接字
//     close(socket1);
//     close(socket2);
    
//     return 0;
// }


int main()
{
    test_clock();
}
