#!/usr/bin/env python

# AUTHOR
#
# Lahis Almeida (lahis.almeida@eldorado.org.br)


# CODE BASED ON
#
# https://github.com/STMicroelectronics/BlueSTSDK_Python/blob/master/blue_st_examples/example_ble_1.py


# DESCRIPTION
#
# This code perform a Bluetooth Low Energy (BLE) scan.


# IMPORT

import sys
import os
import time

from abc import abstractmethod
from blue_st_sdk.manager import Manager

import ble_interfaces


# Scanning time in seconds (optional).
SCANNING_TIME_s = 5


# MAIN APPLICATION

def main(argv):


    try:
        # Creating Bluetooth Manager.
        manager = Manager.instance()
        manager_listener = ble_interfaces.MyManagerListener()
        manager.add_listener(manager_listener)

        while True:
            # Synchronous discovery of Bluetooth devices.
            print('\nScanning Bluetooth devices...\n')
            manager.discover(SCANNING_TIME_s)


            # Getting discovered devices.
            discovered_devices = manager.get_nodes()

            # Listing discovered devices.
            if not discovered_devices:
                print('No Bluetooth devices found. Exiting...\n')
                sys.exit(0)
            print('Available Bluetooth devices:')
            i = 1
            for device in discovered_devices:
                print('%d) %s: [%s]' % (i, device.get_name(), device.get_tag()))
                i += 1

            # Exiting.
            manager.remove_listener(manager_listener)
            print('\nExiting...\n')
            sys.exit(0)

    except KeyboardInterrupt:
        try:
            # Exiting.
            print('\nExiting...\n')
            sys.exit(0)
        except SystemExit:
            os._exit(0)


if __name__ == "__main__":

    main(sys.argv[1:])