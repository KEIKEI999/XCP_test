#include "Xcp_ConfigTypes.h"

#define COUNTOF(a) (sizeof(a)/sizeof(*(a)))

static Xcp_DaqListType* g_channels_daqlist[4][253];


static Xcp_EventChannelType g_channels[] = {
	{.XcpEventChannelNumber = 0
	  ,.XcpEventChannelMaxDaqList = COUNTOF(g_channels_daqlist[0])
	  ,.XcpEventChannelTriggeredDaqListRef = g_channels_daqlist[0]
	  ,.XcpEventChannelName = "Default 10MS"
	  ,.XcpEventChannelRate = 10
	  ,.XcpEventChannelUnit = XCP_TIMESTAMP_UNIT_1MS
	  ,.XcpEventChannelProperties = 1 << 2 /* DAQ  */
											| 1 << 3 /* STIM */
	},
	{.XcpEventChannelNumber = 1
	  ,.XcpEventChannelMaxDaqList = COUNTOF(g_channels_daqlist[1])
	  ,.XcpEventChannelTriggeredDaqListRef = g_channels_daqlist[1]
	  ,.XcpEventChannelName = "Default 10MS"
	  ,.XcpEventChannelRate = 10
	  ,.XcpEventChannelUnit = XCP_TIMESTAMP_UNIT_1MS
	  ,.XcpEventChannelProperties = 1 << 2 /* DAQ  */
											| 1 << 3 /* STIM */
	},
	{.XcpEventChannelNumber = 2
	  ,.XcpEventChannelMaxDaqList = COUNTOF(g_channels_daqlist[2])
	  ,.XcpEventChannelTriggeredDaqListRef = g_channels_daqlist[2]
	  ,.XcpEventChannelName = "Default 100MS"
	  ,.XcpEventChannelRate = 100
	  ,.XcpEventChannelUnit = XCP_TIMESTAMP_UNIT_1MS
	  ,.XcpEventChannelProperties = 1 << 2 /* DAQ  */
											| 1 << 3 /* STIM */
	},
	{.XcpEventChannelNumber = 3
	  ,.XcpEventChannelMaxDaqList = COUNTOF(g_channels_daqlist[3])
	  ,.XcpEventChannelTriggeredDaqListRef = g_channels_daqlist[3]
	  ,.XcpEventChannelName = "Default 1MS"
	  ,.XcpEventChannelRate = 1
	  ,.XcpEventChannelUnit = XCP_TIMESTAMP_UNIT_1MS
	  ,.XcpEventChannelProperties = 1 << 2 /* DAQ  */
											| 1 << 3 /* STIM */
	},
};

Xcp_ConfigType g_DefaultConfig = {
	.XcpEventChannel = g_channels
  ,.XcpSegment = NULL
  ,.XcpInfo = {.XcpMC2File = "XcpSer" }
  ,.XcpMaxEventChannel = COUNTOF(g_channels)
  ,.XcpMaxSegment = 0/*COUNTOF(g_segments)*/

};
