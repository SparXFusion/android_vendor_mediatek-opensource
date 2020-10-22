// This source code is generated by UdpGeneratorTool, not recommend to modify it directly
#ifndef __LbsLogInterface_H__
#define __LbsLogInterface_H__

#include "mtk_socket_utils.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LBS_LOG_INTERFACE_PROTOCOL_TYPE 307
#define LBS_LOG_INTERFACE_BUFF_SIZE 15376

/**
 * The LBS log interface from vendor to system
 */
typedef enum {
    LBS_LOG_INTERFACE_OPEN_LOG = 0,
    LBS_LOG_INTERFACE_CLOSE_LOG = 1,
    LBS_LOG_INTERFACE_WRITE_LOG = 2,
} LbsLogInterface_message_id;


typedef enum {
    LBS_LOG_INTERFACE_LOG_CATEGORY_GPS_LOG = 0,
    LBS_LOG_INTERFACE_LOG_CATEGORY_MPE_LOG = 1,
    LBS_LOG_INTERFACE_LOG_CATEGORY_DUMP_LOG = 2,
} LbsLogInterface_LogCategory;


// LbsLogInterface_LogCategory
const char* LbsLogInterface_LogCategory_to_string(LbsLogInterface_LogCategory data);
void LbsLogInterface_LogCategory_array_dump(LbsLogInterface_LogCategory data[], int size);

void LbsLogInterface_LogCategory_array_init(LbsLogInterface_LogCategory output[], int max_size);

bool LbsLogInterface_LogCategory_is_equal(LbsLogInterface_LogCategory data1, LbsLogInterface_LogCategory data2);
bool LbsLogInterface_LogCategory_array_is_equal(LbsLogInterface_LogCategory data1[], int size1, LbsLogInterface_LogCategory data2[], int size2);

bool LbsLogInterface_LogCategory_encode(char* buff, int* offset, LbsLogInterface_LogCategory data);
bool LbsLogInterface_LogCategory_array_encode(char* buff, int* offset, LbsLogInterface_LogCategory data[], int size);

void LbsLogInterface_LogCategory_decode(char* buff, int* offset, LbsLogInterface_LogCategory* output);
int LbsLogInterface_LogCategory_array_decode(char* buff, int* offset, LbsLogInterface_LogCategory output[], int max_size);

// Sender
bool LbsLogInterface_openLog(mtk_socket_fd* client_fd, LbsLogInterface_LogCategory type, char* filePath);

bool LbsLogInterface_closeLog(mtk_socket_fd* client_fd, LbsLogInterface_LogCategory type);

bool LbsLogInterface_writeLog(mtk_socket_fd* client_fd, LbsLogInterface_LogCategory type, char log[], int log_size);

// Receiver
typedef struct {
    void (*LbsLogInterface_openLog_handler) (LbsLogInterface_LogCategory type, char* filePath);
    void (*LbsLogInterface_closeLog_handler) (LbsLogInterface_LogCategory type);
    void (*LbsLogInterface_writeLog_handler) (LbsLogInterface_LogCategory type, char log[], int log_size);
} LbsLogInterface_callbacks;

bool LbsLogInterface_receiver_decode(char* _buff, LbsLogInterface_callbacks* callbacks);
bool LbsLogInterface_receiver_read_and_decode(int server_fd, LbsLogInterface_callbacks* callbacks);

#ifdef __cplusplus
}
#endif

#endif

