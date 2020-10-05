#!/usr/bin/env python

# Based on: https://github.com/STMicroelectronics/BlueSTSDK_Python/blob/master/blue_st_examples/example_ble_1.py

# DESCRIPTION
#
# This application example shows how to: perform a Bluetooth Low Energy (BLE):
# scan, connect to a device, retrieve its exported features, and get push
# notifications from it.
#
# The code focus is get imu data values


# IMPORT
from __future__ import print_function
import sys
import os
import time
from abc import abstractmethod

from blue_st_sdk.manager import Manager
from blue_st_sdk.manager import ManagerListener
from blue_st_sdk.node import NodeListener
from blue_st_sdk.feature import FeatureListener


# CONSTANTS

STILE_MAC_ADDRESS = "f0:f1:bb:af:02:38"
COORDS_SIZE = 9

MAG_INDEX  = 4
GYRO_INDEX = 5
ACC_INDEX  = 6

SCANNING_TIME_s = 5     # Bluetooth Scanning time in seconds (optional).
NOTIFICATIONS   = 1000    # Number of notifications to get before disabling them.

# ================== INTERFACES ==================
#
# Implementation of the interface used by the Manager class to notify that a new
# node has been discovered or that the scanning starts/stops.
#
class MyManagerListener(ManagerListener):

    #
    # This method is called whenever a discovery process starts or stops.
    #
    # @param manager Manager instance that starts/stops the process.
    # @param enabled True if a new discovery starts, False otherwise.
    #
    def on_discovery_change(self, manager, enabled):
        print('Discovery %s.' % ('started' if enabled else 'stopped'))
        if not enabled:
            print()

    #
    # This method is called whenever a new node is discovered.
    #
    # @param manager Manager instance that discovers the node.
    # @param node    New node discovered.
    #
    def on_node_discovered(self, manager, node):
        print('New device discovered: %s.' % (node.get_name()))


#
# Implementation of the interface used by the Node class to notify that a node
# has updated its status.
#
class MyNodeListener(NodeListener):

    #
    # To be called whenever a node connects to a host.
    #
    # @param node Node that has connected to a host.
    #
    def on_connect(self, node):
        print('Device %s connected.' % (node.get_name()))

    #
    # To be called whenever a node disconnects from a host.
    #
    # @param node       Node that has disconnected from a host.
    # @param unexpected True if the disconnection is unexpected, False otherwise
    #                   (called by the user).
    #
    def on_disconnect(self, node, unexpected=False):
        print('Device %s disconnected%s.' % \
            (node.get_name(), ' unexpectedly' if unexpected else ''))
        if unexpected:
            # Exiting.
            print('\nExiting...\n')
            sys.exit(0)

    def on_status_change(self): # PYTHON 2 COMPATIBILITY
        pass


#
# Implementation of the interface used by the Feature class to notify that a
# feature has updated its data.
#
class MyFeatureListener(FeatureListener):

    _notifications = 0
    _savePackageTimestamp = 0
    _axisList = [] # 18 bytes (ACC, GYR, MAG)
    _auxAxisList = []
    """Counting notifications to print only the desired ones."""

    # To be called whenever the feature updates its data.
    # @param feature Feature that has updated.
    # @param sample  Data extracted from the feature.
    #
    def on_update(self, feature, sample):
        if self._notifications < NOTIFICATIONS:
            self._notifications += 1
            #print(feature)
            #print(type(feature))
            #print(feature.get_name(), sample)
            #print(str(feature.get_name()), sample.get_data())
            if str(feature.get_name()) == "Accelerometer":
                self._savePackageTimestamp = sample.get_timestamp()
                self._auxAxisList.append(sample.get_data()[0])
                self._auxAxisList.append(sample.get_data()[1])
                self._auxAxisList.append(sample.get_data()[2])
            elif str(feature.get_name()) == "Gyroscope" and sample.get_timestamp() == self._savePackageTimestamp:
                self._auxAxisList.append(sample.get_data()[0])
                self._auxAxisList.append(sample.get_data()[1])
                self._auxAxisList.append(sample.get_data()[2])
            elif str(feature.get_name()) == "Magnetometer" and sample.get_timestamp() == self._savePackageTimestamp:
                self._auxAxisList.append(sample.get_data()[0])
                self._auxAxisList.append(sample.get_data()[1])
                self._auxAxisList.append(sample.get_data()[2])

                #Python 3.5:
                #self._axisList = self._auxAxisList.copy()
                #self._auxAxisList.clear()

                #Python 2.7:
                self._axisList = self._auxAxisList[:]
                del self._auxAxisList[:]


    def get_axis(self):
        if len(self._axisList) == COORDS_SIZE:
            return  self._axisList
        else:
            return  None



# ================== MAIN APPLICATION ==================

def main(argv):
    try:
        # Creating Bluetooth Manager.
        manager = Manager.instance()
        manager_listener = MyManagerListener()
        manager.add_listener(manager_listener)

        while True:
            # Synchronous discovery of Bluetooth devices.
            print('Scanning Bluetooth devices...\n')
            manager.discover(SCANNING_TIME_s)

            # Getting discovered devices.
            discovered_devices = manager.get_nodes()
            # Listing discovered devices.
            if not discovered_devices:
                print('No Bluetooth devices found. Exiting...\n')
                sys.exit(0)
            print('Available Bluetooth devices:')

            i = 1
            device_index = 0
            for device in discovered_devices:
                print('%d) %s: [%s]' % (i, device.get_name(), device.get_tag()))
                if device.get_tag() == STILE_MAC_ADDRESS:
                    device_index = i
                    break
                i += 1

            if device_index == 0: # Exiting.
                manager.remove_listener(manager_listener)
                print('Exiting...\n')
                sys.exit(0)

            device = discovered_devices[device_index - 1]
            node_listener = MyNodeListener()
            device.add_listener(node_listener)

            # Connecting to the device.
            print('Connecting to %s...' % (device.get_name()))
            if not device.connect():
                print('Connection failed.\n')
                continue


            while True:
                # Getting features.
                features = device.get_features()

                # Selecting features.
                mag_feature  = features[MAG_INDEX]
                gyro_feature = features[GYRO_INDEX]
                acc_feature  = features[ACC_INDEX]

                print(type(gyro_feature))
                #print(gyro_feature.read_gyroscope())

                # Enabling notifications.
                feature_listener = MyFeatureListener()
                mag_feature.add_listener(feature_listener)
                gyro_feature.add_listener(feature_listener)
                acc_feature.add_listener(feature_listener)

                device.enable_notifications(mag_feature)
                device.enable_notifications(gyro_feature)
                device.enable_notifications(acc_feature)

                # Getting notifications.
                notifications = 0
                while notifications < NOTIFICATIONS:
                    if device.wait_for_notifications(0.05):
                        print(feature_listener.get_axis())
                        notifications += 1

                # Disabling notifications.
                device.disable_notifications(mag_feature)
                mag_feature.remove_listener(feature_listener)

                device.disable_notifications(gyro_feature)
                gyro_feature.remove_listener(feature_listener)

                device.disable_notifications(acc_feature)
                acc_feature.remove_listener(feature_listener)


    except KeyboardInterrupt:
        try:
            # Disconnecting from the device.
            print('\nDisconnecting from %s...' % (device.get_name()))
            if not device.disconnect():
                print('Disconnection failed.\n')

            device.remove_listener(node_listener)
            # Resetting discovery.
            manager.reset_discovery()

            # Exiting.
            print('\nExiting...\n')
            sys.exit(0)
        except SystemExit:
            os._exit(0)


if __name__ == "__main__":

    main(sys.argv[1:])
