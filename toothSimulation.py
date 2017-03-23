#!/usr/bin/python2.7
#
# PiTooth allows the Raspberry Pi to act as a Bluetooth keyboard, and relays
# keypresses from a USB keyboard to a Bluetooth client. Written by Liam Fraser
# for a Linux User & Developer tutorial.
#

import os # Used to call external commands
import sys # Used to exit the script
import bluetooth
from bluetooth import *
import dbus # Used to set up the SDP record
import time # Used for pausing the process
import evdev # Used to get input from the keyboard
from evdev import *
import random
import datetime
import time

class Bluetooth:
    HOST = 0 # BT Mac address
    PORT = 1 # Bluetooth Port Number...

	# Define the ports we'll use
    P_CTRL = 17
    P_INTR = 19
    def __init__(self):
	self.start_time = datetime.datetime.now()
        # Set the device class to a mouse and set the name
        os.system("hciconfig hci0 class 0x002580")
        os.system("hciconfig hci0 name Raspberry Pi")
        # Make device discoverable
        os.system("hciconfig hci0 piscan")
	# Define our two server sockets for communication
	self.scontrol = BluetoothSocket(L2CAP)
	self.sinterrupt = BluetoothSocket(L2CAP)
	# Bind these sockets to a port
	self.scontrol.bind(("", Bluetooth.P_CTRL))
	self.sinterrupt.bind(("", Bluetooth.P_INTR))

        # Set up dbus for advertising the service record
        self.bus = dbus.SystemBus()
        try:
            self.manager = dbus.Interface(self.bus.get_object("org.bluez", "/"), "org.bluez.Manager")
            adapter_path = self.manager.DefaultAdapter()
            self.service = dbus.Interface(self.bus.get_object("org.bluez", adapter_path), "org.bluez.Service")
        except:
            sys.exit("Could not configure bluetooth. Is bluetoothd started?")

         # Read the service record from file
        try:
            fh = open(sys.path[0] + "/sdp_record.xml", "r")
        except:
            sys.exit("Could not open the sdp record. Exiting...")
        self.service_record = fh.read()
        fh.close()


    def listen(self):
        # Advertise our service record
        self.service_handle = self. service.AddRecord(self.service_record)
        print "Service record added"
        # Start listening on the server sockets
        self.scontrol.listen(1) # Limit of 1 connection
        self.sinterrupt.listen(1)
        print "Waiting for a connection"
        self.ccontrol, self.cinfo = self.scontrol.accept()
        print "Got a connection on the control channel from " + self.cinfo[Bluetooth.HOST]
        self.cinterrupt, self.cinfo = self.sinterrupt.accept()
        print "Got a connection on the interrupt channel from " + self.cinfo[Bluetooth.HOST]



    def event_loop(self):
	
        while True:
        #    os.system("./simulation_mouse")
        #    content=""
        #    with open("tmp.txt") as f:
        # 	   for line in f:
        #        	content += chr(int(line.strip('\n'),16))
        #    self.cinterrupt.send(content)
		#if (datetime.datetime.now() - self.start_time).seconds < 5:
		return_val =  chr(0x0) + chr(0xA1) + chr(0x02) + chr(0x0) + chr(0x19) + chr(0x19)  
		#return_val =  chr(0xA1) + chr(0x02) + chr(0010) + chr(0x15)+ chr(0x0) + chr(0x19) + chr(0x19)
		#return_val = chr(int("0xA1",16)) + chr(int("0x02",16)) + chr(int("0x01",16)) + chr(int("0x19",16)) + chr(int("0x19",16))
		print "sending to host : D:" + return_val + ":F"
		self.cinterrupt.send(return_val)
		time.sleep(5)

            



if __name__ == "__main__":
    # We can only run as root
    if not os.geteuid() == 0:
        sys.exit("Only root can run this script")
    bt = Bluetooth()
    bt.listen()
    bt.event_loop();





