#ifndef SHAIRPORT_SYNC_METADATA_READER_H
#define SHAIRPORT_SYNC_METADATA_READER_H

#include <string>

class ShairportSyncMetadataReader {
public:
    ShairportSyncMetadataReader();
    void run();
    std::string getMetadata() const;
    std::string getOtherData() const;

private:
    std::string pipe_name;
    int pipe_fd;
 
    // Variables to store metadata and other messages
    std::string metadata;
    std::string otherData;

    void openPipe();
    void processMetadata();
    void handleMessage(const char* msg, ssize_t len);
    std::string decodeBase64(const std::string& encoded);
    bool isBase64(unsigned char c);
    ~ShairportSyncMetadataReader();
};

#endif // SHAIRPORT_SYNC_METADATA_READER_H
