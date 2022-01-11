import ctypes
import sys

print("REF_CREATOR")

def saveRef():
    with open("ref_created.txt","w") as f :
        pass

if __name__ == "__main__":
    for i, arg in enumerate(sys.argv):
        print(f"Argument {i:>2}: {arg}")