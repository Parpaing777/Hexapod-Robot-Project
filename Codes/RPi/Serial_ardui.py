import serial
import time
import KeyPressModule as kp

time.sleep(1)
kp.init()

def main():
	if kp.getKey('UP'):
		ser.write(b'1')
		time.sleep(0.1)
	elif kp.getKey('DOWN'):
		ser.write(b'2')
		time.sleep(0.1)
	elif kp.getKey('LEFT'):
		ser.write(b'3')
		time.sleep(0.1)
	elif kp.getKey('RIGHT'):
		ser.write(b'4')
		time.sleep(0.1)
	else:
		ser.write(b'0')
		time.sleep(0.1)

if __name__== '__main__' :
	ser = serial.Serial('/dev/ttyACM0', 9600, timeout =1)
	ser.reset_input_buffer()
	while True:
		main()
