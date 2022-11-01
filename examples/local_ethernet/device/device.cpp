#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>
//#include "syndesi_config.h"
#include <syndesicp.h>

using namespace std;
using namespace syndesi;

syndesi::Core core;

void callback();

int new_socket;

syndesi::SyndesiID id;
class IPController : public syndesi::SAP::IController {
    int server_fd;
    int opt = 1;

    int sock = 0;

    struct sockaddr_in address;
    const int addrlen = sizeof(address);

   public:
    IPController(SAP::INetwork_bottom* _network) : IController(_network){};

    void init() {
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }
        // Forcefully attaching socket to the port 8080
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                       sizeof(opt))) {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(IPPort());

        if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }

        if (listen(server_fd, 3) < 0) {
            perror("listen");
            exit(EXIT_FAILURE);
        }
    }

    void write(SyndesiID& deviceID, char* buffer, size_t length) {
        int sock = 0;
        struct sockaddr_in serv_addr;

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(deviceID.getIPPort());
        if (inet_pton(AF_INET, deviceID.str().c_str(), &serv_addr.sin_addr) <= 0) {
            printf("\nInvalid address/ Address not supported \n");
            return;
        }

        int bytes_sent = send(new_socket, buffer, length, 0);
    }

    size_t read(char* buffer, size_t length) {
        int valread = ::read(new_socket, buffer, length);

        /*for (int i = 0; i < valread; i++) {
            printf("%02X ", (uint8_t)buffer[i]);
        }*/
        return valread;
    }

    void close() { ::close(new_socket); }

    void wait_for_connection() {
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address,
                                 (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        hostID.fromIPv4(address.sin_addr.s_addr, address.sin_port);
        dataAvailable();
    }

    SyndesiID& getSyndesiID() { return hostID; }

    SyndesiID hostID;

    void end() { shutdown(server_fd, SHUT_RDWR); }
};

IPController controller(&core.network);

int main(int argc, char const* argv[]) {
    char buffer[1024] = {0};

    cout << "Syndesi comtest example : device" << endl;
    cout << "Sébastien Deriaz    20.08.2022" << endl;

    core.init();

    while (1) {
        controller.wait_for_connection();
    }

    return 0;
}

void syndesi::Callbacks::DEVICE_DISCOVER_request_callback(
    syndesi::DEVICE_DISCOVER_request& request,
    syndesi::DEVICE_DISCOVER_reply* reply) {
    cout << "DEVICE_DISCOVER_request_callback" << endl;
}

void syndesi::Callbacks::REGISTER_READ_16_request_callback(
    syndesi::REGISTER_READ_16_request& request,
    syndesi::REGISTER_READ_16_reply* reply) {
    cout << "REGISTER_READ_16_request_callback" << endl;
    cout << "    Address = " << request.address << endl;
    reply->data = request.address;
    cout << "    reply value : " << reply->data << endl;
}

void syndesi::Callbacks::REGISTER_WRITE_16_request_callback(
    syndesi::REGISTER_WRITE_16_request& request,
    syndesi::REGISTER_WRITE_16_reply* reply) {
    cout << "REGISTER_WRITE_16_request_callback" << endl;
    cout << "    address = " << request.address << endl;
    cout << "    data = " << request.data << endl;
    cout << "    reply value : ok" << endl;
    reply->status = REGISTER_WRITE_16_reply::OK;
}
void syndesi::Callbacks::SPI_READ_WRITE_request_callback(
    syndesi::SPI_READ_WRITE_request& request,
    syndesi::SPI_READ_WRITE_reply* reply) {
    cout << "SPI_READ_WRITE_request_callback" << endl;
    cout << "    interface index = " << request.interface_index;
    cout << "    data = " << request.write_data.toHex() << " ("
         << request.write_size << ")" << endl;
    string response = "<SPI_READ_WRITE reply>";
    // reply->read_data = Buffer(response.c_str(), response.length());
    reply->read_size = reply->read_data.length();
}
void syndesi::Callbacks::SPI_WRITE_ONLY_request_callback(
    syndesi::SPI_WRITE_ONLY_request& request,
    syndesi::SPI_WRITE_ONLY_reply* reply) {
    cout << "SPI_WRITE_ONLY_request_callback" << endl;
    cout << "SPI_READ_WRITE_request_callback" << endl;
    cout << "    interface index = " << request.interface_index;
    cout << "    data = " << request.write_data.toHex() << " ("
         << request.write_size << ")" << endl;
    cout << "    reply value : OK" << endl;
    reply->status = SPI_WRITE_ONLY_reply::OK;
}
void syndesi::Callbacks::I2C_READ_request_callback(
    syndesi::I2C_READ_request& request, syndesi::I2C_READ_reply* reply) {
    cout << "I2C_READ_request_callback" << endl;
    cout << "    interface index = " << request.interface_index;
    cout << "    read size = " << request.read_size << endl;

    string response = "<I2C_READ_request reply>";
    // reply->read_data = Buffer(response);
    reply->read_size = reply->read_data.length();
    cout << "    reply data = " << reply->read_data.toHex() << " ("
         << reply->read_size << ")" << endl;
}
void syndesi::Callbacks::I2C_WRITE_request_callback(
    syndesi::I2C_WRITE_request& request, syndesi::I2C_WRITE_reply* reply) {
    cout << "I2C_WRITE_request_callback" << endl;
    cout << "    interface index = " << request.interface_index;
    cout << "    data = " << request.write_data.toHex() << " ("
         << request.write_size << ")" << endl;

    cout << "    reply value : OK" << endl;
    reply->status = I2C_WRITE_reply::OK;
}
