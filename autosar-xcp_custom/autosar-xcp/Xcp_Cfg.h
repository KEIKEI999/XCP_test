#ifndef XCP_CFG_H_
#define XCP_CFG_H_

#include "Xcp_ConfigTypes.h"

#define XCP_PROTOCOL	XCP_PROTOCOL_CAN

#define	XCP_STANDALONE	1

#define	BYTE_ORDER	CPU_BYTE_ORDER

#define	XCP_DEV_ERROR_DETECT	STD_ON
/*
XCP_PDU_ID_TX :
The PDU id the Xcp submodule will use when transmitting data using
CanIf or SoAd.
*/
#define XCP_PDU_ID_TX	0

/*
XCP_PDU_ID_RX :
The PDU id the Xcp submodule will expect data on when it's callbacks 
are called CanIf or SoAd.
*/

#define XCP_PDU_ID_RX	1

/*
XCP_CAN_ID_RX :
If GET_SLAVE_ID feature is wanted over CAN, XCP must know what CAN id it
is receiving data on.
*/
#define	XCP_CAN_ID_RX	2

/*
XCP_PDU_ID_BROADCAST :
If GET_SLAVE_ID feature is wanted over CAN, XCP must know what PDU id it
will receive broadcasts on
*/
//#define	XCP_PDU_ID_BROADCAST

/*
XCP_E_INIT_FAILED :
Error code for a failed initialization.Should have been defined by DEM.
*/

#define	XCP_E_INIT_FAILED	111

/*
XCP_COUNTER_ID :
Counter id for the master clock Xcp will use when sending DAQ lists
this will be used as an argument to AUTOSAR GetCounterValue.
*/
#define XCP_COUNTER_ID	1

/*
XCP_TIMESTAMP_SIZE :
Number of bytes used for transmitting timestamps(0; 1; 2; 4).If clock
has higher number of bytes, Xcp will wrap timestamps as the max
byte size is reached.Set to 0 to disable timestamp support
*/
#define XCP_TIMESTAMP_SIZE	2

/*
XCP_IDENTIFICATION :
Defines how ODT's are identified when DAQ lists are sent. Possible	values are :
	XCP_IDENTIFICATION_ABSOLUTE:
		All ODT's in the slave have a unique number.
	XCP_IDENTIFICATION_RELATIVE_BYTE :
	XCP_IDENTIFICATION_RELATIVE_WORD :
	XCP_IDENTIFICATION_RELATIVE_WORD_ALIGNED :
		ODT's identification is relative to DAQ list id.
		Where the DAQ list is either byte or word sized.
		And possibly aligned to 16 byte borders.

	Since CAN has a limit of 8 bytes per packets, this will
	modify the limit on how much each ODT can contain.
*/
#define XCP_IDENTIFICATION	XCP_IDENTIFICATION_ABSOLUTE

/*
XCP_MAX_RXTX_QUEUE:
Number of data packets the protocol can queue up for processing.
This should include send buffer aswell as STIM packet buffers.
This should at the minimum be set to
	1 recieve packet + 1 send packet + number of DTO objects that
	can be configured in STIM mode + allowed interleaved queue size.
*/
#define XCP_MAX_RXTX_QUEUE	100

/*
XCP_FEATURE_DAQSTIM_DYNAMIC : (STD_ON; STD_OFF)[Default:STD_OFF]
Enables dynamic configuration of DAQ lists instead of
statically defining the number of lists aswell as their
number of odts / entries at compile time.
*/
#define XCP_FEATURE_DAQSTIM_DYNAMIC	STD_ON

/*
XCP_FEATURE_BLOCKMODE : (STD_ON; STD_OFF)[Default:STD_OFF]
Enables XCP blockmode transfers which speed up Online Calibration
transfers.
*/
#define XCP_FEATURE_BLOCKMODE	STD_OFF

/*
XCP_FEATURE_PGM : (STD_ON; STD_OFF)[Default:STD_OFF]
Enables the programming / flashing feature of Xcp
(NOT IMPLEMENTED)
*/
#define XCP_FEATURE_PGM	STD_OFF

/*
XCP_FEATURE_CALPAG : (STD_ON; STD_OFF)[Default:STD_OFF]
Enabled page switching for Online Calibration
(NOT IMPLEMENTED)
*/
#define XCP_FEATURE_CALPAG	STD_OFF

/*
XCP_FEATURE_DAQ : (STD_ON; STD_OFF)[Default:STD_OFF]
Enabled use of DAQ lists.Requires setup of event channels
and the calling of event channels from code :
Xcp_MainFunction_Channel()
*/
#define XCP_FEATURE_DAQ	STD_ON

/*
XCP_FEATURE_STIM(STD_ON; STD_OFF)[Default:STD_OFF]
Enabled use of STIM lists.Requires setup of event channels
and the calling of event channels from code :
	Xcp_MainFunction_Channel()
*/
#define XCP_FEATURE_STIM	STD_ON

/*
XCP_FEATURE_DIO(STD_ON; STD_OFF)[Default:STD_OFF]
Enabled direct read / write support using Online Calibration
to AUTOSAR DIO ports using memory exstensions :
	0x2 : DIO port
	0x3 : DIO channel
All ports are considered to be of sizeof(Dio_PortLevelType)
bytes long.So port 5 is at memory address 5 * sizeof(Dio_PortLevelType)
Channels are of BYTE length.
*/
#define XCP_FEATURE_DIO	STD_OFF

/*
XCP_FEATURE_GET_SLAVE_ID(STD_ON; STD_OFF)[Default:STD_OFF]
Enable GET_SLAVE_ID support over the CAN protocol.
Needs the following additional config :
XCP_PDU_ID_BROADCAST
	XCP_CAN_ID_RX
*/
#define XCP_FEATURE_GET_SLAVE_ID	STD_OFF

/*
	XCP_FEATURE_PROTECTION :
Enables seed and key protection for certain features.
Needs configured callback functions in XcpConfig for
the seed calculation and key verification.
*/
//#define XCP_FEATURE_PROTECTION

/*
XCP_MAX_DTO : [Default:CAN = 8, IP = 255]
XCP_MAX_CTO : [Default:CAN = 8, IP = 255]
Define the maximum size of a data / control packet.This will also
directly affect memory consumptions for XCP since the code will
always allocate XCP_MAX_DTO * XCP_MAX_RXTX_QUEUE bytes for
data buffers.
*/
#define XCP_MAX_DTO	8
#define XCP_MAX_CTO 8


#endif /* XCP_CFG_H_ */