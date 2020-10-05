#!/usr/bin/env python


# DESCRIPTION
#
# This application example shows how to perform a Bluetooth Low Energy (BLE)
# scan, connect to a device, retrieve its exported features, and get push
# notifications from it.


# IMPORT
from __future__ import print_function
import sys
import os

from blue_st_sdk.manager import Manager
from blue_st_sdk.features.audio.adpcm.feature_audio_adpcm import FeatureAudioADPCM
from blue_st_sdk.features.audio.adpcm.feature_audio_adpcm_sync import FeatureAudioADPCMSync

import ble_interfaces


# CONSTANTS

# Bluetooth Scanning time in seconds (optional).
SCANNING_TIME_s = 5

# Sensortile Mac Address
SENSORTILE_MAC_ADDRESS = "ce:ea:9c:a0:f6:8a"
#SENSORTILE_MAC_ADDRESS = "MAC ADDRESS OF YOUR SENSORTILE BOARD"


# MAIN APPLICATION

def main(argv):

    try:
        # Creating Bluetooth Manager.
        manager = Manager.instance()
        manager_listener = ble_interfaces.MyManagerListener()
        manager.add_listener(manager_listener)

        # Synchronous discovery of Bluetooth devices.
        print('Scanning Bluetooth devices...\n')
        manager.discover(SCANNING_TIME_s)

        # Getting discovered devices.
        discovered_devices = manager.get_nodes()
        if not discovered_devices:
            print('No Bluetooth devices found. Exiting...\n')
            sys.exit(0)
        
        sensortile_index = -1
        for device in discovered_devices:
            if device.get_tag() == SENSORTILE_MAC_ADDRESS:
                sensortile_index = discovered_devices.index(device)
                break

        # Exiting.
        if sensortile_index == -1: 
            manager.remove_listener(manager_listener)
            print('Exiting...\n')
            sys.exit(0)

        device = discovered_devices[sensortile_index]
        node_listener = ble_interfaces.MyNodeListener()
        device.add_listener(node_listener)

        # Connecting to the device.
        print('Connecting to %s [%s] ...' % (device.get_name(), device.get_tag()))
        if not device.connect():
            print('Connection failed... Try again!\n')
            print('Exiting...\n')
            sys.exit(0)
        

        # Getting features.
        features = device.get_features()
        print('\nAvailable Features:')
        i = 1
        for feature in features:
            if isinstance(feature, FeatureAudioADPCM):
                audio_feature = feature
                print('%d,%d) %s' % (i,i+1, "Audio & Sync"))
                i+=1
            elif isinstance(feature, FeatureAudioADPCMSync):
                audio_sync_feature = feature
            else:
                print('%d) %s' % (i, feature.get_name()))
                i+=1

        # Exiting.
        manager.remove_listener(manager_listener)

        # Disconnecting from the device.
        print('\nDisconnecting from %s [%s] ...' % (device.get_name(), device.get_tag()))
        if not device.disconnect():
            print('Disconnection failed.\n')

        device.remove_listener(node_listener)
        print('Exiting...\n')
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