
# Author: Pierce Brooks

import os
import re
import sys

def join(path):
	result = ""
	length = len(path)
	for i in range(length):
		result += path[i]
		if not (i == length-1):
			result += "/"
	return result

def run(target, pattern, replacement, extensions):
	replace = True
	report = False
	entries = True
	paths = []
	length = len(replacement)
	all = 0
	for root, folders, files in os.walk(target):
		names = []
		for name in files:
			names.append([name, False])
		for name in folders:
			names.append([name, True])
		for name in names:
			folder = name[1]
			name = name[0]
			if not (folder):
				if not (len(extensions) == 0):
					skip = True
					for extension in extensions:
						if (len(name) > len(extension)):
							if (name[(len(name)-len(extension)):] == extension):
								skip = False
								break
					if (skip):
						continue
			path = os.path.join(root, name)
			print(path+"\n")
			if not (folder):
				handle = open(path, "r")
				lines = handle.readlines()
				handle.close()
				content = ""
				index = 0
				total = 0
				for line in lines:
					index += 1
					new = ""
					matches = map(lambda x: x, re.finditer(pattern, line))
					count = len(matches)
					if (count == 0):
						new = line
					else:
						total += count
						if (report):
							print("Line: "+str(index))
							print("Old: \""+line.strip()+"\"")
							print("Matches: "+str(count))
						for i in range(count):
							match = matches[i]
							start = match.start(0)
							end = match.end(0)
							old = match.group(0)
							if (i == 0):
								if not (start == 0):
									new += line[0:start]
							else:
								new += line[(matches[i-1].end(0)):start]
							new += replacement
						new += line[(matches[count-1].end(0)):]
						if (report):
							print("New: \""+new.strip()+"\"\n")
					content += new
				if (total > 0):
					all += total
					if not (report):
						print("Matches: "+str(total)+"\n")
					if (replace):
							handle = open(path, "w")
							handle.write(content)
							handle.close()
			if (entries):
				new = ""
				matches = map(lambda x: x, re.finditer(pattern, path))
				count = len(matches)
				if (count == 0):
					new = path
				else:
					if (report):
						print("Old: \""+path.strip()+"\"")
						print("Matches: "+str(count))
					for i in range(count):
						match = matches[i]
						start = match.start(0)
						end = match.end(0)
						old = match.group(0)
						if (i == 0):
							if not (start == 0):
								new += path[0:start]
						else:
							new += path[(matches[i-1].end(0)):start]
						new += replacement
					new += path[(matches[count-1].end(0)):]
					if (report):
						print("New: \""+new.strip()+"\"\n")
					paths.append([path, new, folder])
	replacements = []
	for path in paths:
		old = path[0].replace("\\", "/")
		new = path[1].replace("\\", "/")
		folder = path[2]
		old = old.split("/")
		new = new.split("/")
		length = len(old)
		if (length == len(new)):
			for i in range(length):
				if not (old[i] == new[i]):
					then = join(old[0:i])
					now = then
					then += "/"+old[i]
					now += "/"+new[i]
					pair = [then, now]
					if (i == length-1):
						pair.append(folder)
					else:
						pair.append(True)
					if not (pair in replacements):
						replacements.append(pair)
		else:
			print("Error!\n")
	for i in range(len(replacements)):
		pair = replacements[i]
		then = pair[0]
		now = pair[1]
		folder = pair[2]
		print(then+" -> "+now+" ("+str(folder)+")\n")
		if (replace):
			os.rename(then, now)
		all += 1
	print("Done!\n")
	print("Operations: "+str(all)+"\n")

if (__name__ == "__main__"):
	arguments = sys.argv
	length = len(arguments)
	if (length > 3):
		if (length > 4):
			run(arguments[1], arguments[2], arguments[3], arguments[4:])
		else:
			run(arguments[1], arguments[2], arguments[3], [])
