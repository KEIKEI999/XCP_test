from io import StringIO
from pyxcp.config import readConfiguration
from pyxcp import transport
from pyxcp.transport.candriver.pc_vector import Vector # "CAN_DRIVER": "Vector"を指定する場合に必要
from pyxcp.master import Master
from collections import namedtuple
import time
import collections
import matplotlib.pyplot as plt

class xcp_can:
	def __init__ ( self,reqid=1, resid=2, bitrate=500000, appname="PyXCP-CAN", serial=0 ):
		# コンフィグレーションパラメータ(JSON文字列)の作成と読み込み
		JSON = """{
		"TRANSPORT": "CAN",
		"CAN_DRIVER": "Vector",
		"CAN_USE_DEFAULT_LISTENER": true,
		"CHANNEL": "0",
		"CAN_ID_MASTER":""" + str(resid) + """ ,
		"CAN_ID_SLAVE": """ + str(reqid) + """,
		"CAN_ID_BROADCAST": 256,
		"MAX_DLC_REQUIRED": false,
		"CREATE_DAQ_TIMESTAMPS": true,
		"SERIAL": """ + str(serial) + """,
		"BITRATE": """ + str(bitrate) + """,
		"APP_NAME": """ + "\"" + appname + "\""  + """
		}"""
		CONF_JSON = StringIO(JSON)
		CONF_JSON.name = "conf_can_vector.json"
		CONFIG = readConfiguration(CONF_JSON)
		
		# コンフィグレーションを元にXCPマスターの生成
		self.xm = Master('can',config=CONFIG)
		
	def setup( self ):
		# CONNECT
		conn = self.xm.connect()
		print(conn)
		
		# GET_STATUS
		status = self.xm.getStatus()
		print(status)
		
		# GET_COMM_MODE_INFO
		CommModeInfo = self.xm.getCommModeInfo()
		print(CommModeInfo)
		
		# DAQリストの構築
		self.xm.freeDaq();
		self.xm.allocDaq(2);
		self.xm.allocOdt(0, 1);
		self.xm.allocOdt(1, 1);
		self.xm.allocOdtEntry(0, 0, 3);
		self.xm.allocOdtEntry(1, 0, 2);
		
		# ODT_ENTRYへの書き込み
		DaqEntry = namedtuple("DaqEntry", "daq odt entry bitoff size ext addr")
		de0 = (
			# DAQ 0
			DaqEntry(daq=0, odt=0,  entry=0, bitoff=255, size=2, ext=0xff, addr=0x00000100),
			DaqEntry(daq=0, odt=0,  entry=1, bitoff=255, size=2, ext=0xff, addr=0x00000102),
			DaqEntry(daq=0, odt=0,  entry=2, bitoff=255, size=2, ext=0xff, addr=0x00000104),
			
			# DAQ 1
			DaqEntry(daq=1, odt=0,  entry=0, bitoff=255, size=2, ext=0xff, addr=0x00000100),
			DaqEntry(daq=1, odt=0,  entry=1, bitoff=255, size=2, ext=0xff, addr=0x00000102),
		)
		for daq, odt, entry, bitoff, size, ext, addr in de0:
			self.xm.setDaqPtr(daq, odt,  entry)
			self.xm.writeDaq(bitoff, size, ext, addr)
		
		# DAQ開始可能状態
		self.xm.setDaqListMode(0x00, 0, 2, 1, 0)
		self.xm.setDaqListMode(0x02, 1, 3, 1, 0)

		res = self.xm.startStopDaqList(0x02, 0)
		print("startStopDaqList #0", res)
		res = self.xm.startStopDaqList(0x02, 1)
		print("startStopDaqList #1", res)
		
	def start_daq( self ):
		# DAQ起動
		self.xm.startStopSynch(0x01);
		
	def stop_daq( self ):
		# DAQ停止
		self.xm.startStopSynch(0x01);
		
	def stim( self, target,input):
		targetL = int(target) & 0xFF
		targetH = int(target/0x100) & 0xFF
		inputL = int(input) & 0xFF
		inputH = int(input/0x100) & 0xFF
		sndmsg = bytearray(
			[0x01, targetL, targetH, inputL, inputH, ],
		)
		self.xm.transport.send(sndmsg)
	
	def write( self, addr, data ):
		self.xm.setMta(addr,0xff)
		bhv = bytearray(data)
		self.xm.download(bhv)
	
	def recv_daq( self ):
		daqdata=dict()
		queue_len = len(self.xm.transport.daqQueue)
		for _ in range(queue_len):
			daq = self.xm.transport.daqQueue.popleft()
			pid = int(daq[0][0])
			daqdata[str(pid)] = daq	# PID単位でディクショナリ登録(同一PIDなら上書きされ最新値だけが残る)
		return daqdata
	
	def close( self ):
		self.xm.disconnect()
		self.xm.close()

if __name__ == '__main__':
	xcp = xcp_can()
	xcp.setup()
	xcp.start_daq()
	
	stim_wait = 1.0
	start = time.time()
	stim_time =  time.time()+stim_wait-0.03

	ram_update = [
		[100*0x100, 0*0x100],
		[100*0x100, 60*0x100],
		[100*0x100, 80*0x100],
		[100*0x100, 95*0x100],
		[100*0x100, 110*0x100],
		[100*0x100, 95*0x100],
		[100*0x100, 110*0x100],
		[100*0x100, 100*0x100],
		[  0*0x100, 100*0x100],
		[  0*0x100,   0*0x100],
	]
	
	deque_time = collections.deque()
	deque_target = collections.deque()
	deque_input = collections.deque()
	deque_output = collections.deque()
	
	i = 0
	print_str = ""
	try:
		while True:
			daq = xcp.recv_daq()
			if len(daq) > 0:
				print_str += '%.6f, %s\n' % ( daq['0'][3],daq['0'][0].hex() )
				deque_time.append(time.perf_counter())
				deque_target.append( float(int.from_bytes(daq['0'][0][1:3], byteorder='little', signed=True))/0x100 )
				deque_input.append( float(int.from_bytes(daq['0'][0][3:5], byteorder='little', signed=True))/0x100 )
				deque_output.append( float(int.from_bytes(daq['0'][0][5:7], byteorder='little', signed=True))/0x100 )
				if time.time() > stim_time:
					xcp.stim(ram_update[i][0], ram_update[i][1])
					print_str += 'stim %s %s\n' % ( hex(ram_update[i][0]), hex(ram_update[i][1]) )
					stim_time =  stim_time + stim_wait
					i = i+1
					if i > len(ram_update)-1:
						i = len(ram_update)-1
			if time.time() > start + 12:
				break
			time.sleep(0.010)
	except KeyboardInterrupt:
		pass
	
	print(print_str)
	
	xcp.stop_daq()
	xcp.close()
	
	plt.plot(deque_time, deque_target, marker='.', color='Magenta',linewidth=3, label="target[rad/s]")
	plt.plot(deque_time, deque_input, marker='.', color='Blue',linewidth=0.9, label="input[rad/s]")
	plt.plot(deque_time, deque_output, marker='.',  color='Red', label="output[V]")
	plt.legend()
	plt.grid(which='both')
	
	plt.show()
	
