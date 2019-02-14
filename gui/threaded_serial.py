import threading
import serial

port = 'COM7'
baud = 9600

serial_port = serial.Serial(port, baud)


def handle_data(data):
	print(data.rstrip())


def read_from_port(ser):
	while True:
		print("test")
		reading = ser.readline().decode('utf-8')
		handle_data(reading)


thread = threading.Thread(target=read_from_port, args=(serial_port,))
thread.start()
