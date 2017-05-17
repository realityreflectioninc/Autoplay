import json
import os
import subprocess
import sys

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

def isPassTest(result):
    if len(result["FailedAssertions"]) is not 0:
        return False
    
    for value in result["RoutineCheckList"]:
        if value is 0:
            return False
    
    return True

if len(sys.argv) is not 2:
    print("use Autoplay.py (config file path)")
    sys.exit()

config_path = sys.argv[1]
result_path = "Tests\\Result\\result.json"

with open(config_path) as config_file:
    config = json.load(config_file)

editor_path = os.path.join(config["EditorPath"], "UE4Editor.exe")
passed = 0
failed = 0

# auto play
for level in config["Autoplay"]:
    project_path = os.path.join(os.getcwd(), config["Project"])
    subprocess.call([editor_path, project_path, level, "-game", "-autoplay"])
    
    # result check
    with open(result_path) as result_file:
        result = json.load(result_file)

    if isPassTest(result):
        passed+=1
        print(level, "result :" + bcolors.OKGREEN, "pass", bcolors.ENDC)
    else:
        failed+=1
        print(level, "result :" + bcolors.FAIL, "fail", bcolors.ENDC)
        for message in result["FailedAssertions"]:
            print("\tassertion failed :", message)
        
        for routine in result["RoutineCheckList"].items():
            if routine[1] is 0:
                print("\troutine not execute :", routine[0])

print(bcolors.HEADER + "test result : pass", passed, "cases, fail", failed, "cases" + bcolors.ENDC)