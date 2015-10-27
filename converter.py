import wave
import sys
import struct

input = wave.open(sys.argv[1],'r')
output = open(sys.argv[2], 'w')

framerate = input.getframerate()
numFrames = input.getnframes()


output.write("// *************************\n//Converted by Chris Frame and Troy Ellis\n\n\nint soundRate = ")
output.write(str(framerate))
output.write("\nint numFrames = ")
output.write(str(numFrames))
output.write("\n\nint sound[] = {")


for i in range(0, numFrames):
	frame = input.readframes(1)
	temp = struct.unpack("<2B", frame)
	output.write(str(temp[0]))
	output.write(",")
	output.write(str(temp[1]))
	if i == numFrames -1:
		output.write("")
	else:
		output.write(",")

output.write("\n}")
output.close()
