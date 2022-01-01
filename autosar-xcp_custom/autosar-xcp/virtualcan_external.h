#define	VIRTUAL_CAN_DLL
#ifdef VIRTUAL_CAN_DLL 
#define DECLSPEC_DLLPORT	__declspec(dllexport)
#else
#define DECLSPEC_DLLPORT	__declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"{
#endif

// CAN_IDタイプ 
typedef enum
{
	VCAN_ID_STD = 0x00, // standard ID 11 Bit
	VCAN_ID_EXT = 0x01,  // extended ID 29 Bit
	VCAN_ID_OWN = 0x02,
} VCAN_ID_TYPE;

// CAN frameタイプ
typedef enum
{
	VCAN_FRAME_DATA = 0x00, // data frame
	VCAN_FRAME_RTR  = 0x01  // remote frame
} VCAN_FRAME_TYPE;

// CAN messages (ISO 11898)
typedef struct vcanMessage_tag
{
	unsigned long				Time;	// TimeStamp;
	unsigned long				Id;		// 11 Bit or 29 Bit CAN identifier
	VCAN_ID_TYPE		Ext;    // CAN_ID_STD = 11 Bit CAN_ID, CAN_ID_EXT = 29 Bit CAN_ID
	VCAN_FRAME_TYPE	Rtr;    // CAN_FRAME_DATA = data frame, CAN_FRAME_RTR = remote frame
	unsigned char				Dlc;    // data length code (0 - 8)
    unsigned char				Data[64];// data frame
} vcanMessage;

typedef int (*vcan_callbackUpdate)(void*,vcanMessage*);				//!< 通知用コールバック関数

DECLSPEC_DLLPORT void* viratualCanInit( int ch, vcan_callbackUpdate rx_interrupt, vcan_callbackUpdate tx_interrupt, vcan_callbackUpdate err_interrupt, void *param, char* username, int OnDebug  );
DECLSPEC_DLLPORT int viratualCanConfig( void* handle, unsigned long arbrate,unsigned long datarate );
DECLSPEC_DLLPORT int viratualCanStart( void* handle );
DECLSPEC_DLLPORT int viratualCanStop( void* handle );
DECLSPEC_DLLPORT int viratualCanSend( void*, vcanMessage* msg, int fd );


#ifdef __cplusplus
}
#endif