import os
import ctypes

full_path = os.path.abspath('./main.dll')
dll = ctypes.CDLL(full_path)

print(dll.test_function(2, 1, 4000, 100))