import subprocess
import os


# Get the env variables
halide_include_path = os.environ.get('HALIDE_INCLUDE_PATH')
halide_shared_lib_path = os.environ.get('HALIDE_SHARED_LIB_PATH')

# Compile and run the C code
subprocess.run(["gcc", "XAXPY.c", "-o", "XAXPY"])
c_result = subprocess.run(["./XAXPY"], capture_output=True, text=True)

print("Results of the C version :")
print(c_result.stdout)

# Compile and run the Halide code

# We use env variables to setup the args of the command
if halide_include_path and halide_shared_lib_path:
    subprocess.run(["g++" , "halide-XAXPY.cpp" , "-g" , f"-I{halide_include_path}", f"-L{halide_shared_lib_path}" , "-lHalide" , 
                        "-lpthread" , "-ldl", "-o" "halide-XAXPY" ,  "-std=c++17"])
    
    halide_result = subprocess.run(["./halide-XAXPY"], capture_output=True, text=True, 
                        env=dict(os.environ, LD_LIBRARY_PATH=halide_shared_lib_path))

# Assuming that Halide is built systemwide
else:
    subprocess.run(["g++" , "halide-XAXPY.cpp" , "-g" , "-lHalide" , "-lpthread" , "-ldl", "-o" "halide-XAXPY" ,  "-std=c++17"])
    halide_result = subprocess.run(["./halide-XAXPY"], capture_output=True, text=True)

print("Results of the Halide version :")
print(halide_result.stdout)
