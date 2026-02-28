import os
import platform
import subprocess

from SetupAndCompile import CompileBuildFiles

(selected_generator, selected_config) = CompileBuildFiles()

target_name = "sandbox"
print(f"\nRunning \"{target_name}\" in {selected_config} configuration")
exe_path = os.path.join(f"build/{selected_generator}", "bin", selected_config, f"{target_name}")
if platform.system() == "Windows":
	subprocess.run([f"{exe_path}.exe"], cwd=os.path.dirname(exe_path))
else:
	subprocess.run([f"{exe_path}"], cwd=os.path.dirname(exe_path))
