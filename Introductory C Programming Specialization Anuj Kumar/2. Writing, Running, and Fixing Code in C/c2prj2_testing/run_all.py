import random
import shutil
import subprocess

ranks = list('234567890JQKA')
suits = list('shdc')

count = '1'

def make_hand():
    hand = ''
    for i in range(7):
        hand += random.choice(ranks) + random.choice(suits) + ' '
    return hand.strip()

while count == '1':
    shutil.copyfile('tests1.txt', 'tests.txt')
    f = open('tests.txt', 'a')
    f.write(make_hand() + '; ' + make_hand() + '\n')
    f.close()
    p = subprocess.Popen("./run_all.sh", stdout=subprocess.PIPE, shell=True)

    output, err = p.communicate()
    p_status = p.wait()
    if p_status:
        print("Command exit status/return code : ", p_status)
        break;
    lines = output.decode("utf-8").split('\n')
    if len(lines) >= 2:
        line = output.decode("utf-8").split('\n')[-2]
        if len(line) > 30:
            count = line[30]

print("Count: ", count)