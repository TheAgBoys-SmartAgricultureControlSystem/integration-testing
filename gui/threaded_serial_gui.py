import threading
import serial
import time
import datetime
import collections
import io
from tkinter import *





class Nodes:
	numModules = 5
	Node = collections.namedtuple('node', ['nodeid', 'rssi', 'lat', 'lng', 'soil'])
	node0 = Node(nodeid=None, rssi=None, lat=None, lng=None, soil=None)
	node1 = Node(nodeid=None, rssi=None, lat=None, lng=None, soil=None)
	node2 = Node(nodeid=None, rssi=None, lat=None, lng=None, soil=None)
	node3 = Node(nodeid=None, rssi=None, lat=None, lng=None, soil=None)


class Window(Frame):
	def __init__(self, master=None):

		super(Window, self).__init__()
		Frame.__init__(self, master)
		Grid.config(self)

		# control frame:
		self.control = LabelFrame(master, width=640, height=240, text="Control")
		self.control.grid(row=0, column=0, rowspan=1)
		self.control.grid_propagate(True)
		# testing frame:
		self.testing = LabelFrame(master, width=640, height=240, text="Test")
		self.testing.grid(row=1, column=0)
		self.testing.grid_propagate(True)

		# initialise serial communication
		try:
			self.serial_port = serial.Serial(
				port='COM7',
				baudrate=9600,
				parity="N",
				stopbits=1,
				bytesize=8,
				timeout=8
			)
		except serial.SerialException:
			print("Error connecting")
			exit()

		thread = threading.Thread(target=self.read_from_port, args=())
		thread.start()
		print("Connection Made")
		self.init_window()

	def init_window(self):
		self.pos_lbl = Label(self.control, text="")
		self.pos_lbl.grid(column=3, row=1)
		self.checkPos = Label(self.control, text="Current Position")
		self.checkPos.grid(column=3, row=0)
		self.nextButton = Button(self.testing, text="Next", command=self.set_modules)
		self.nextButton.grid(column=2, row=4)

	def read_from_port(self):
		while True:
			self.reading = self.serial_port.readline().decode('utf-8')
			# self.handle_data(reading)
			self.reading = self.reading.rstrip('\n')
			self.global_data = str(self.reading)
			try:
				if str(self.global_data).isspace():
					pass
				else:
					self.global_data = self.global_data.split('#')
					if self.global_data[0][7:] == '0':
						Nodes.node0 = Nodes.node0._replace(nodeid=self.global_data[0][7:], rssi=self.global_data[4][5:], lat=self.global_data[2][9:],
												   lng=self.global_data[3][10:], soil=self.global_data[1][13:])
					if self.global_data[0][7:] == '1':
						Nodes.node1 = Nodes.node1._replace(nodeid=self.global_data[0][7:], rssi=self.global_data[4][5:], lat=self.global_data[2][9:],
												   lng=self.global_data[3][10:], soil=self.global_data[1][13:])
					if self.global_data[0][7:] == '2':
						Nodes.node2 = Nodes.node2._replace(nodeid=self.global_data[0][7:], rssi=self.global_data[4][5:], lat=self.global_data[2][9:],
												   lng=self.global_data[3][10:], soil=self.global_data[1][13:])
					if self.global_data[0][7:] == '3':
						Nodes.node3 = Nodes.node3._replace(nodeid=self.global_data[0][7:], rssi=self.global_data[4][5:], lat=self.global_data[2][9:],
												   lng=self.global_data[3][10:], soil=self.global_data[1][13:])
			except IndexError:
				pass

	def set_modules(self):
		self.pos_lbl.configure(text=Nodes.node1.rssi)
	# 	while True:
	# 		if (Nodes.node0.nodeid or Nodes.node1.nodeid or Nodes.node2.nodeid or Nodes.node3.nodeid) is None:
	# 			print("Acquiring")
	# 			time.sleep(20)
	# 		else:
	# 			print(Nodes.node0)
	# 			time.sleep(0.1)
	# 			print(Nodes.node1)
	# 			time.sleep(0.1)
	# 			print(Nodes.node2)
	# 			time.sleep(0.1)
	# 			print(Nodes.node3)
	# 			time.sleep(0.1)


def main():
	root = Tk()
	Window(root)
	root.mainloop()


if __name__ == "__main__":
	main()
