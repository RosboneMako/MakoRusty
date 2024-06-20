# Mako Rusty
A demo Juce VST Guitar Amplifier Simulation. 
* Tested on Windows only.
* Written in Visual C++ 2022.
* Written for new programmers, not complicated.
* Version: 1.00
* Posted: June 20, 2024

VERSION
------------------------------------------------------------------
1.00 - Initial release.

DISCLAIMER
------------------------------------------------------------------  
This VST was written in a very simple way. No object defs, etc. 
Just simple code for people who are not programmers but want to 
dabble in the magic of JUCE VSTs.

If you are new to JUCE code, the Mako Thump VST may be a better
starting place. Or be brave and try this.
       
SUMMARY
------------------------------------------------------------------
A Juce/C++ VST3 written to simulate an older style guitar amplifier. 

![Demo Image](docs/assets/rustydemo01.jpg)

# THEORY OF OPERATION<br />
This VST is designed to mimic a low gain guitar amplifier. It applies an EQ to the guitar signal before it
applies any gain. 

The guitar signal chain thru the VST is:  
Guitar -> Noise Gate -> Compressor -> Low Cut -> EQ -> Gain -> Impulse Response Speaker Sim

COMPRESSOR  
Since the VST is trying to duplicate and older style cleanish amp, a compressor was added to bring out the
jingle and allow for close to breakup sounds. 

The single control is for the compressor THRESHOLD. This is the volume the incoming signal must hit to trigger the
compressor. 

A setting of 1.0 (Full On) means the compressor is off and not being used.  
A setting of 3 o'clock will largely compress the signal and is good for edge of breakup type sounds.  

LOW CUT  
As the gain is increased, low frequencies will overwhelm the distortion stage creating a muffled bassy sound.
Having a low cut filter lets you reduce some of the very low frequencies before gain. The default value is 80 Hz.
The range of the control is 20 - 200 Hz.

EQ  
The VST uses a simple 5 band EQ style filter style. There are 11 EQs avaialaibe with varying Cutoff Frequencies (Fc) 
and filter Q's.

GAIN   
The signal gathers gain thru the EQ section. That signal is then sent thru some soft clipping code to add distortion.
The overall distortion is a combination of EQ, Gain, and compressor settings. 


