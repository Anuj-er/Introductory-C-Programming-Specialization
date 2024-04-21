
import subprocess

p = subprocess.Popen("date", stdout=subprocess.PIPE, shell=True)

output, err = p.communicate()
p_status = p.wait()

print("Command output : ", output)
print("Command exit status/return code : ", p_status);