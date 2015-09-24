from tables import *


class DESpy():
	def __init__(self):
		pass


	def XOR(self, bitsA, bitsB):
		
		if len(bitsA) != len(bitsB):
			raise Exception("Strings must be same length in order to XOR")

		newBits = ["1"]*len(bitsA)
		for i in range(len(bitsA)):
			if bitsA[i] == bitsB[i]:
				newBits[i] = "0"
		return "".join(newBits)
	# end XOR()


	def left_shift(self, bits, num_shifts=1):
		
		oldBits = list(bits)
		newBits =  [None]*len(bits)

		for i in range(num_shifts):
			newBits = [None]*len(bits)
			for j in range(len(oldBits)):
				newBits[j-1] = oldBits[j]
			oldBits = newBits

		newString = "".join(newBits)
		return newString
	# end left_shift()


	def permute_key_with_pc1(self, key):
		if len(key) != 64:
			raise Exception("Key length must be 64 bits.")
		for char in key:
			if char != '0' and char != '1':
				raise Exception("Key must contain only 0's and 1's.")
		
		permuted_key = [None]*56
		for i in range(len(PC1_TABLE)):
			permuted_key[i] = key[PC1_TABLE[i] - 1]
		return ''.join(permuted_key)
	# end permute_key_with_pc1()


	def create_shifted_blocks(self, init_block):
		blocks = []
		cur_block = init_block
		for num_shifts in SHIFT_TABLE:
			next_block = self.left_shift(cur_block, num_shifts)
			blocks.append(next_block)
			cur_block = next_block
		return blocks
	# end create_shifted_blocks()


	def permute_key_with_pc2(self, key):
		if len(key) != 56:
			raise Exception("Key length must be 56 bits.")
		for char in key:
			if char != '0' and char != '1':
				raise Exception("Key must contain only 0's and 1's.")

		permuted_key = [None]*48
		for i in range(len(PC2_TABLE)):
			permuted_key[i] = key[PC2_TABLE[i] - 1]
		return ''.join(permuted_key)
	# end permute_key_with_pc2()


	def initial_permutation(self, message):
		if len(message) != 64:
			raise Exception("Message length must be 64 bits.")
		for char in message:
			if char != '0' and char != '1':
				raise Exception("Message must contain only 0's and 1's.")
		
		permuted_message = [None]*64
		for i in range(len(IP_TABLE)):
			permuted_message[i] = message[IP_TABLE[i] - 1]
		return ''.join(permuted_message)	
	# end initial_permutation()


	def e_bit_selection(self, right_block):
		if len(right_block) != 32:
			raise Exception("Block length must be 32 bits. "
							"Found length of {0}".format(len(right_block)))
		for char in right_block:
			if char != '0' and char != '1':
				raise Exception("Block must contain only 0's and 1's.")
		
		permuted_block = [None]*48
		for i in range(len(E_BIT_TABLE)):
			permuted_block[i] = right_block[E_BIT_TABLE[i] - 1]
		return ''.join(permuted_block)
	# end e_bit_selection()


	def s_box_selection(self, bits, box_num):
		if len(bits) != 6:
			raise Exception("Must use only 6 bits for S box selection.")
		for char in bits:
			if char != '0' and char != '1':
				raise Exception("Bits must contain only 0's and 1's.")
		s_box = S[box_num]
		row_bits = bits[0] + bits[5]
		row = int(row_bits, 2)
		column_bits = bits[1:5]
		column = int(column_bits, 2)

		# this is the actual index in the S table list
		index = (row*16) + (column)
		
		value = "{0:04b}".format(s_box[index])
		return value
	# end s_box_selection()


	def build_s_box_output(self, data):
		if len(data) != 48:
			raise Exception("Must use only 6 bits for S box selection.")
		for char in data:
			if char != '0' and char != '1':
				raise Exception("Data must contain only 0's and 1's.")
		pieces = []
		pieces.append(data[0:6])
		pieces.append(data[6:12])
		pieces.append(data[12:18])
		pieces.append(data[18:24])
		pieces.append(data[24:30])
		pieces.append(data[30:36])
		pieces.append(data[36:42])
		pieces.append(data[42:])

		selections = []
		for i in range(len(pieces)):
			new_selection = self.s_box_selection(pieces[i], i+1)
			selections.append(new_selection)
		return ''.join(selections)
	# end build_s_box_output()


	def p_permutation(self, data):
		if len(data) != 32:
			raise Exception("Length of data must be 32 bits.")
		for char in data:
			if char != '0' and char != '1':
				raise Exception("Data must contain only 0's and 1's.")
		
		permuted_data = [None]*32
		for i in range(len(P_TABLE)):
			permuted_data[i] = data[P_TABLE[i] - 1]
		return ''.join(permuted_data)
	# end p_permutation()


	def feistel(self, data, key):
		
		e_expansion = self.e_bit_selection(data)
		xored = self.XOR(key, e_expansion)
		# insert length check here -- must be 48 bits
		s_box_output = self.build_s_box_output(xored)
		# insert length check here -- must be 32 bits
		p_permuted = self.p_permutation(s_box_output)
		return p_permuted
	# end feistel()


	def iterations(self, L_zero, R_zero, keys):
		# insert length checks for l_zero and r_zero?
		# insert check for num keys?
		
		keys = [None] + keys
		print "keys {0}".format(keys)
		print "num keys: {0}".format(len(keys))
		left_blocks = [None]*17
		right_blocks = [None]*17
		left_blocks[0] = L_zero
		right_blocks[0] = R_zero

		for n in range(1, 17):
			print "n = {0}".format(n)
			left_blocks[n] = right_blocks[n-1]

			#print "new left block = {0}".format(left_blocks[n])
			feistel = self.feistel(right_blocks[n-1], keys[n])
			#print "feistel = {0}".format(feistel)
			right_blocks[n] = self.XOR(left_blocks[n-1], feistel)
			#print "we do {0}".format(left_blocks[n-1])
			#print "XOR   {0}".format(feistel)
			#print "& get {0}".format(right_blocks[n])
			print hex(int(left_blocks[n],2)),"    ",hex(int(right_blocks[n],2))
			print ""

		return (left_blocks[16], right_blocks[16])
	# end iterations()


	def final_permutation(self, data):
		if len(data) != 64:
			raise Exception("Length of data must be 64 bits.")
		for char in data:
			if char != '0' and char != '1':
				raise Exception("Data must contain only 0's and 1's.")
		
		permuted_data = [None]*64
		for i in range(len(IP_INVERSE_TABLE)):
			permuted_data[i] = data[IP_INVERSE_TABLE[i] - 1]
		return ''.join(permuted_data)
	# end final_permutation()

	
	def encrypt(self, plain_text, key):
		
		# (i) permute key using PC-1 table (to 56 bit key)
		permuted_key = self.permute_key_with_pc1(key)
		if len(permuted_key) != 56:
			raise Exception("Length of permuted key should be 56 bits.")

		# (ii) split into left and right halves (C0 and D0, 28 bits each)
		c_zero = permuted_key[0:28]
		d_zero = permuted_key[28:]

		# (iii) from C0 and D0, create 16 blocks from each using left shifts table
		c_blocks = self.create_shifted_blocks(c_zero)
		d_blocks = self.create_shifted_blocks(d_zero)

		# (iv) from each CnDn form key Kn by using PC-2 table (48 bits)
		keys = []
		for i in range(len(c_blocks)):
			pair = c_blocks[i] + d_blocks[i]
			new_key = self.permute_key_with_pc2(pair)
			keys.append(new_key)
		
		# (i) apply initial permutation by using IP table on 64-bit data
		initial_permutation = self.initial_permutation(plain_text)

		# (ii) divide IP block into L0 and R0 halves, 32 bits each
		L_zero = initial_permutation[0:32]
		R_zero = initial_permutation[32:]

		# (iii) iterate 16 times
		iterated_blocks = self.iterations(L_zero, R_zero, keys)
		
		# (iv) swap the blocks and apply final permutation IP^-1
		swapped_blocks = (iterated_blocks[1], iterated_blocks[0])
		encrypted_data = self.final_permutation(swapped_blocks[0] + swapped_blocks[1])
		
		
		return encrypted_data
	# end encrypt()



dev = DESpy()
#plaintext="0000000100100011010001010110011110001001101010111100110111101111"
#key=      "0001001100110100010101110111100110011011101111001101111111110001"
plaintext= "0000001001000110100010101100111011101100101010000110010000100000"
key =      "0000111100010101011100011100100101000111110110011110100001011001"
print hex(int(dev.encrypt(plaintext,key),2))



