import subprocess, os

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def	remove_file():
	if os.path.exists("file.txt"):
		os.remove("file.txt")
	if os.path.exists("file1.txt"):
		os.remove("file1.txt")

def	send_stdin(input_data, proc):
	if (input_data):
		proc.stdin.write(input_data.encode())
		proc.stdin.flush()  # Flush the input buffer to make sure all data is sent
		out = proc.communicate()[0].decode().splitlines()
	else:
		out = proc.communicate()[0].decode().splitlines()
	return (out)


with open("assert_cmds.txt", "r") as f:
	nl = 0;
	error_count = 0
	redirection = False
	heredoc = False
	input_data = None
	print(f"{bcolors.UNDERLINE}{bcolors.HEADER}Beginning of Assertion")
	print(f"{bcolors.UNDERLINE}{bcolors.HEADER}CYAN LINES are stderr from minishell and bash, not actual errors{bcolors.OKCYAN}")
	for line in f:
		nl += 1
		if (line.startswith('#')):
			if ("END REDIRECTION" in line):
				redirection = False
			elif ("START REDIRECTION" in line):
				redirection = True
			elif ("START HEREDOC" in line):
				heredoc = True
			elif ("END HEREDOC" in line):
				heredoc = False
			continue
		line = line.strip()

		# Run the first program with the arguments from the current line
		if (heredoc):
			input_data = "hello\nworld\n4"
			proc1 = subprocess.Popen(["./minishell", line], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
			out1 = send_stdin(input_data, proc1)
		else:
			proc1 = subprocess.Popen(["./minishell", line], stdout=subprocess.PIPE)
			out1 = send_stdin(input_data, proc1)
		remove_file()

		# Run the second program with the same arguments
		if (heredoc):
			input_data = "hello\nworld\n4"
			proc2 = subprocess.Popen(["bash", "-c", line], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
			out2 = send_stdin(input_data, proc2)
		else:
			proc2 = subprocess.Popen(["bash", "-c", line], stdout=subprocess.PIPE)
			out2 = send_stdin(input_data, proc2)
		remove_file()

		try:
			assert out1 == out2, f"{bcolors.FAIL}Outputs for arguments {bcolors.WARNING}'{line}'{bcolors.FAIL} do not match{bcolors.OKCYAN}\n{out1}\n{out2}"
		except AssertionError as e:
			print(f"{bcolors.WARNING}line {nl}{bcolors.ENDC}", e)
			error_count += 1
	else:
		if (error_count == 0):
			print(f"{bcolors.OKGREEN}All tests passed{bcolors.ENDC}")
	remove_file()
