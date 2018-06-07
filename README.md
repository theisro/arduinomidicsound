# About
Arduino code for running on a Due. Creates the arduino as a midi input device and sends notes based on button press. Potentiometer is used to control frequency. Csound file to read input and play a physical modeled instrument - wgbow.

# Instructions

midi.ino is to be used with bow_keys.csd. Upload the sketch to the Arduino Due, connect the Due through USB to your computer. Run `csound bow_keys.csd`

midi_multipot.ino is to be used with bow_keys_multipot.csd.
