#include "Std_Types.h"
#include "ComStack_Types.h"
#include "virtualcan_external.h"
#include "XcpOnCan_Cbk.h"
#include "Xcp.h"

extern void _Sleep(unsigned int ms);
extern void _timeBeginPeriod(unsigned int ms);
extern unsigned int _timeGetTime();
extern void* _CreateMutex(void* lpMutexAttributes, int bInitialOwner, char* lpName);
extern unsigned int _WaitForSigleObject(void* hHandle, unsigned int dwMilliseconds);
extern int _ReleaseMutex(void* hMutex);
extern void setcallback(void(*pcallback)());
void *pVcanHandle = NULL;
void* hMutex;
PduInfoType XcpInfo;

int cycle_cnt;

extern Xcp_ConfigType	g_DefaultConfig;

static uint8 candf_dlc_convert( length )
{
	uint8 dlc = 0;
	if (length <= 8) {
		dlc = length;
	}else if (8 < length && length <= 12) {
		dlc = 9;
	}else if (12 < length && length <= 16) {
		dlc = 0xA;
	}else if (16 < length && length <= 20) {
		dlc = 0xB;
	}else if (20 < length && length <= 24) {
		dlc = 0xC;
	}else if (24 < length && length <= 32) {
		dlc = 0xD;
	}else if (32 < length && length <= 48) {
		dlc = 0xE;
	}else if (48 < length && length <= 64) {
		dlc = 0xF;
	}

	return dlc;
}

Std_ReturnType _CanIf_Transmit(PduIdType CanTxPduId, const PduInfoType *PduInfoPtr)
{
	size_t i;
	vcanMessage msg = { 0 };
	msg.Dlc = PduInfoPtr->SduLength;
	int fd = 0;

#ifdef CANFD_SUPPORT
	fd = 1;
	msg.Dlc = candf_dlc_convert(PduInfoPtr->SduLength);
#endif
	
	if (CanTxPduId == 0) {
		msg.Id = 2;
	}
	msg.Ext = VCAN_ID_STD;

	for (i = 0U; i < PduInfoPtr->SduLength; i++) {
		msg.Data[i] = PduInfoPtr->SduDataPtr[i];
	}

	viratualCanSend(pVcanHandle, &msg, fd);
	return(BUFREQ_OK);
}

int rx_interrupt(void *param, vcanMessage* msg)
{
	_WaitForSigleObject(hMutex, -1);

	// for CAN-FD
	static const uint8 cantp_canfd_dlc_snd_table[] = {
	0U,		1U,		2U,		3U,		4U,		5U,		6U,		7U,
	8U,		12U,	16U,	20U,	24U,	32U,	48U,	64U,
	};

	XcpInfo.SduDataPtr = msg->Data;
	XcpInfo.SduLength = cantp_canfd_dlc_snd_table[msg->Dlc];
	if (msg->Id == 1) {
		Xcp_CanIfRxIndication(1, &XcpInfo);
	}
	_ReleaseMutex(hMutex);
	return 0;
}

int tx_interrupt(void *param, vcanMessage* msg)
{
	return 0;
}

int err_interrupt(void *param, vcanMessage* msg)
{
	return 0;
}

void main_handler()
{
	_WaitForSigleObject(hMutex, -1);
	

	ecu_t1ms_job();
	if (cycle_cnt % 10 == 0) {
		ecu_t10ms_job();
	}

	if (cycle_cnt % 100 == 0) {
		ecu_t100ms_job();
	}
	if (cycle_cnt % 200 == 0) {
		ecu_t200ms_job();
	}

	
	Xcp_MainFunction();

	Xcp_MainFunction_Channel(3);

	if (cycle_cnt % 10 == 0) {
		Xcp_MainFunction_Channel(1);
	}

	if (cycle_cnt % 100 == 0){
		Xcp_MainFunction_Channel(2);
	}
	cycle_cnt++;
	_ReleaseMutex(hMutex);
}

void XcpStandaloneLock()
{
	_WaitForSigleObject(hMutex, -1);
}

void XcpStandaloneUnlock()
{
	_ReleaseMutex(hMutex);
}

void Det_ReportError(uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
	printf("Det_ReportError ModuleId=%d, InstanceId=%d, ApiId=%d, ErrorId=%d \n", ModuleId, InstanceId, ApiId, ErrorId);
}

int main()
{
	syslog(LOG_NOTICE, "=== MainTask ===");

	hMutex = _CreateMutex(NULL_PTR, FALSE, (char*)NULL_PTR);

	_timeBeginPeriod(1);
	pVcanHandle = viratualCanInit(0, rx_interrupt, tx_interrupt, err_interrupt, 0, "autosar-xcp", 1);
	viratualCanConfig(pVcanHandle, 500000, 2000000);
	viratualCanStart(pVcanHandle);

	syslog(LOG_NOTICE, "== XcpTp_Init ==");
	
	ecu_init();
	Xcp_Init(&g_DefaultConfig);
	

	_Sleep(1);
	setcallback(main_handler);

	return 0;
}
