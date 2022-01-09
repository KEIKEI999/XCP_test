import can
import matplotlib.pyplot as plt
import collections
import time

def xcp_mon(resid=2):
	# バス接続
	bus = can.interface.Bus(bustype='vector', channel='0', bitrate=500000)

	queue_max=3000
	
	deque_target = collections.deque(maxlen=queue_max)
	deque_input = collections.deque(maxlen=queue_max)
	deque_output = collections.deque(maxlen=queue_max)
	deque_time = collections.deque(maxlen=queue_max)
	
	plt.ion()
	fig = plt.figure()
	ax = plt.subplot(1,1,1)
	ax.set_xlabel('Time')
	ax.set_ylabel('Value')
	fig.show()

	# define plots
	ax.plot([], [], label="target[rad/s]", color='Magenta', marker='.',linewidth=1,markersize=5)
	ax.plot([], [], label="voltage[V]", color='Red', marker='.',linewidth=0.8,markersize=5)
	ax.plot([], [], label="speed[rad/s]", color='Blue', marker='.',linewidth=0.7,markersize=5)

	#ax.legend(bbox_to_anchor=(1, 1), loc='bottom right', borderaxespad=0, fontsize=10)
	ax.legend(bbox_to_anchor=(1, 1), borderaxespad=0, fontsize=10)
	ax.grid(which='both')

	current_time = time.perf_counter()
	# 受信
	while True:
		while True:
			recv_msg = bus.recv(timeout=0.0)
			if recv_msg != None:
				if resid == recv_msg.arbitration_id:
					if recv_msg.data[0] == 0x00 :
						print('Recv msg : %s' % recv_msg)
						
						target = float(int.from_bytes(recv_msg.data[1:3], byteorder='little', signed=True))/0x100
						input = float(int.from_bytes(recv_msg.data[3:5], byteorder='little', signed=True))/0x100
						output = float(int.from_bytes(recv_msg.data[5:7], byteorder='little', signed=True))/0x100
						
						deque_target.append(target)
						deque_input.append(input)
						deque_output.append(output)
						deque_time.append(time.perf_counter())
			else:
				break
		if len(deque_time) != 0:
			if time.perf_counter() > (current_time + 0.2):
				ax.lines[0].set_data( deque_time, deque_target )
				ax.lines[1].set_data( deque_time, deque_output )
				ax.lines[2].set_data( deque_time, deque_input )
				ax.relim()                  # recompute the data limits
				ax.autoscale_view()         # automatic axis scaling
				ax.set_ylim(-50,200)
				ax.set_xlim(deque_time[-1]-30,deque_time[-1])
				fig.canvas.flush_events()


if __name__ == '__main__':
	try:
		xcp_mon()
	except KeyboardInterrupt:
		pass
