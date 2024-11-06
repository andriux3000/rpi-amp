#include "metadata.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <poll.h>
#include <cstring>
#include <cstdlib>
#include <vector>

ShairportSyncMetadataReader::ShairportSyncMetadataReader() : pipe_name("/tmp/pipe"), pipe_fd(-1) {}

void ShairportSyncMetadataReader::run() {
    openPipe();
    processMetadata();
}

std::string ShairportSyncMetadataReader::getMetadata() const {
    return metadata;
}

std::string ShairportSyncMetadataReader::getOtherData() const {
    return otherData;
}

void ShairportSyncMetadataReader::openPipe() {
    if ((pipe_fd = open(pipe_name.c_str(), O_RDONLY)) < 0) {
        std::cerr << "Failed to open pipe " << pipe_name << std::endl;
        exit(1);
    }
}

void ShairportSyncMetadataReader::processMetadata() {
    struct pollfd fds[1];
    fds[0].fd = pipe_fd;
    fds[0].events = POLLIN;

    char buffer[1024];
    while (true) {
        int ret = poll(fds, 1, -1);
        if (ret > 0) {
            if (fds[0].revents & POLLIN) {
                ssize_t len = read(pipe_fd, buffer, sizeof(buffer) - 1);
                if (len > 0) {
                    buffer[len] = '\0';
                    handleMessage(buffer, len);
                }
            }
        } else {
            std::cerr << "Polling error" << std::endl;
            break;
        }
    }
}

void ShairportSyncMetadataReader::handleMessage(const char* msg, ssize_t len) {
    std::string message(msg, len);

    // Store message based on its type and decode Base64 if needed
    if (message.find("ssnc") != std::string::npos) {
        if (message.find("mdst") != std::string::npos) {
            metadata = "Metadata start received: " + decodeBase64(message);
        } else if (message.find("mden") != std::string::npos) {
            metadata = "Metadata end received: " + decodeBase64(message);
        } else {
            metadata = "Unrecognized metadata: " + decodeBase64(message);
        }
    } else {
        otherData = "Other data received: " + decodeBase64(message);
    }
}

std::string ShairportSyncMetadataReader::decodeBase64(const std::string& encoded) {
    static const std::string base64_chars =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/";

        std::vector<unsigned char> decoded_data;
        int in_len = encoded.size();
        int i = 0;
        int j = 0;
        int in_ = 0;
        unsigned char char_array_4[4], char_array_3[3];

        while (in_len-- && (encoded[in_] != '=') && isBase64(encoded[in_])) {
            char_array_4[i++] = encoded[in_]; in_++;
            if (i == 4) {
                for (i = 0; i < 4; i++) {
                    char_array_4[i] = base64_chars.find(char_array_4[i]);
                }

                char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
                char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
                char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

                for (i = 0; (i < 3); i++) {
                    decoded_data.push_back(char_array_3[i]);
                }
                i = 0;
            }
        }

        if (i) {
            for (j = i; j < 4; j++) {
                char_array_4[j] = 0;
            }

            for (j = 0; j < 4; j++) {
                char_array_4[j] = base64_chars.find(char_array_4[j]);
            }

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);

            for (j = 0; (j < i - 1); j++) {
                decoded_data.push_back(char_array_3[j]);
            }
        }

        return std::string(decoded_data.begin(), decoded_data.end());
}

bool ShairportSyncMetadataReader::isBase64(unsigned char c){
    return (isalnum(c) || (c == '+') || (c == '/'));
}

ShairportSyncMetadataReader::~ShairportSyncMetadataReader() {
    if (pipe_fd != -1) {
        close(pipe_fd);
    }
}
