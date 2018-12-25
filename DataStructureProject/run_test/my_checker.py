def fc(file_name_1 , file_name_2):

	def deal(line):
		def fil(x):
			return x
		line = line.strip().split(" ")
		line = [x for x in filter(fil , line)]
		line.sort()
		return line

	tot = 0
	good = 0

	try:
		lines1 = []
		lines2 = []

		with open(file_name_1 , "r") as fil1:
			for line in fil1:
				lines1.append( line )
		with open(file_name_2 , "r") as fil2:
			for line in fil2:
				lines2.append( line )

		if len(lines1) < len(lines2):
			lines1 , lines2 = lines2 , lines1

		for i in range( len(lines2) ):
			line1 = lines1[i]
			line2 = lines2[i]

			line1 = deal(line1)
			line2 = deal(line2)

			if len(line1) < len(line2):
				line1 , line2 = line2 , line1

			tot += len(line1)

			for i in range( len(line2) ):
				if line1[i] == line2[i]:
					good += 1

		for i in range( len(lines2) , len(lines1) ):
			line = deal(lines1[i])
			tot += len(line)
	except Exception:
		return 0.

	return good / tot

