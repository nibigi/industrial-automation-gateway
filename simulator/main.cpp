
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include "printer_state.h"

#include <cerrno>
#include <cstring>
#include <iostream>
#include <string>

int main() {
    constexpr int PORT = 5000;
    PrinterStateMachine printer;

    int server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        std::cerr << "Socket error\n";
        return 1;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

    if (bind(server, reinterpret_cast<sockaddr*>(&address),
             sizeof(address)) < 0) {
        std::cerr << "Bind error: " << strerror(errno) << "\n";
        close(server);
        return 1;
    }

    if (listen(server, 5) < 0) {
        std::cerr << "Listen error\n";
        close(server);
        return 1;
    }

    std::cout << "Printer Simulator V0.1\n";
    std::cout << "Listening on 127.0.0.1:5000\n";

    while (true) {
        int client = accept(server, nullptr, nullptr);
        if (client < 0) {
            continue;
        }

        char buffer[1024]{};
        ssize_t received = recv(client, buffer, sizeof(buffer), 0);

        if (received > 0) {
            std::string command(buffer, received);

            while (!command.empty() &&
                   (command.back() == '\n' ||
                    command.back() == '\r')) {
                command.pop_back();
            }

            std::cout << "Received: " << command << std::endl;

            std::string response = printer.execute(command);

            send(client, response.c_str(), response.size(), 0);
        }

        close(client);
    }

    close(server);
    return 0;
}
