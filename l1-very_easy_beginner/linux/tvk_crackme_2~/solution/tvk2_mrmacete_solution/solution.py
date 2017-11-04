import datetime, sys

"""
hex digits permutation table
"""
decoder = ['q','w','E','1','t','y','m','5','B','v','C','X','7','0','f','G']

"""
maps a hex digit to the correct one according to the decoder array
"""
def mapdigit(digit):
	return decoder[int(digit, 16)]


"""
encodes a number in hex format, using the decoder array to permute
hex digits into apparently random alphanumerics
"""
def num_to_hex(num):
	
	enc = [mapdigit(c) for c in hex(num).replace("0x", "")]

	padding = [mapdigit("0")] * (8-len(enc))

	return "".join(padding + enc)

"""
flip all bits of an int
"""
def int_flip(num):
	return 0x100000000 -  num - 1

"""
given the username generates number A
"""
def argv1_to_numberA(argv1):
	"""
	init to zero
	"""
	num = 0

	"""
	accumulate by summing all chars, each multiplied by its counter value
	"""
	for i in range(len(argv1)):
		num += ord(argv1[i]) * i

	now = datetime.datetime.now()
	
	"""
	multiply the result by (minute+hour) value
	"""
	num *= now.minute + now.hour
	
	"""
	flip each bit of the result
	"""
	return int_flip(num)

"""
given the username generates number B
"""
def argv1_to_numberB(argv1):
	"""
	init to zero
	"""
	num = 0

	"""
	accumulate by summing all chars, each summed to the double of its counter value
	"""
	for i in range(len(argv1)):
		num += ord(argv1[i]) + 2*i

	now = datetime.datetime.now()
	
	"""
	add (minute+hour) value to the result
	"""
	num += now.minute + now.hour
	
	"""
	xor with the magic constant
	"""
	return num ^ 0xa318751

"""
given the username generates number C
"""
def argv1_to_numberC(argv1):
	"""
	init to zero
	"""
	num = 0

	"""
	accumulate by simply summing all chars
	"""
	for i in range(len(argv1)):
		num += ord(argv1[i])

	now = datetime.datetime.now()
	
	"""
	add minute and hour in a twisted way to the result
	"""
	num += (now.minute + (now.minute << 4)) + ((now.hour << 5) - now.hour)
	
	"""
	bit mangling by shifting left
	"""
	return num << 4

"""
given the username generates number D
"""
def argv1_to_numberD(argv1):

	now = datetime.datetime.now()

	"""
	init to a value dependent by hour and minute
	"""
	num = now.hour * 0x7d + now.minute

	"""
	accumulate by summing all chars, after combining them in a twisted way to the counter
	"""
	for i in range(len(argv1)):
		num += ord(argv1[i]) << (i & 0x7)

	
	"""
	add minute and hour in a twisted way to the result
	"""
	num += now.minute + ( now.hour << 0x7 )
	
	"""
	no bitwise mangling here
	"""
	return num


if __name__ == "__main__":

	# default username, provide yours via command line args
	argv1 = "porcodio"

	if len(sys.argv) >= 2:
		argv1 = sys.argv[1]

	# generate the four numbers, given the username
	A = argv1_to_numberA(argv1)	
	B = argv1_to_numberB(argv1)
	C = argv1_to_numberC(argv1)
	D = argv1_to_numberD(argv1)

	# assemble the command line
	print "./tvk_crackme_2 {0} {1}{2}{3}{4}".format(argv1, num_to_hex(B), num_to_hex(C), num_to_hex(D), num_to_hex(A) )

