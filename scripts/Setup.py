import os
import subprocess

import Utils
(system, arch) = Utils.GetPlatform()

from SetupPython import PythonConfiguration as PythonRequirements

def GenerateBuildFiles():
	if system not in ["Windows", "Linux", "MacOSX"]:
		print("Platform not supported or unknown")
	else:
		print(f"Detected platform: {system}-{arch}\n")
		try:
			print("Checking Python...")
			if (not PythonRequirements.Validate()):
				raise Exception("PythonException")

			print("\nChecking git submodules...")
			subprocess.run(["git", "submodule", "update", "--init"], check=True)
			print("Done")

			if system == "Windows":
				import inquirer
			from SetupCMake import CMakeConfiguration as CMakeRequirements
			from SetupWindow import WindowConfiguration as WindowRequirements
			os.chdir('./../') # Change from scripts directory to root

			print("\nChecking CMake...")
			if (not CMakeRequirements.Validate()):
				raise Exception("CMakeException")
			print("\nChecking Window libraries support...")
			if (not WindowRequirements.Validate()):
				raise Exception("WindowException")

			print("\nRunning CMake...")

			if system == "Windows":
				generators = [
					("Visual Studio 2022", "Visual Studio 17 2022", "vs2022"),
					("Visual Studio 2019", "Visual Studio 16 2019", "vs2019"),
					("Visual Studio 2017", "Visual Studio 15 2017", "vs2017"),
					("Visual Studio 2015", "Visual Studio 14 2015", "vs2015"),
					("Ninja", "Ninja", "ninja"),
					("Makefile (MinGW)", "MinGW Makefiles", "make")
				]
			elif system == "MacOSX":
				generators = [
					("Xcode", "Xcode", "xcode"),
					("Ninja", "Ninja", "ninja"),
					("Unix Makefiles", "Unix Makefiles", "make")
				]
			else:
				generators = [
					("Ninja", "Ninja", "ninja"),
					("Unix Makefiles", "Unix Makefiles", "make"),
					("CodeLite", "CodeLite - Unix Makefiles", "codelite")
				]

			if system == "Windows":

				choices = [label for label, _, _ in generators]

				question = [
					inquirer.List(
						"generator",
						message="Choose a build system",
						choices=choices,
						carousel=True
					)
				]

				answer = inquirer.prompt(question)
				selected_label = answer["generator"]

				final_dir = ""
				for label, generator, dir in generators:
					if label == selected_label:
						selected_generator = generator
						final_dir = dir
						break

			else:
				print("\nChoose a build system:")
				for idx, (label, _, _) in enumerate(generators, 1):
					print(f"{idx}. {label}")

				try:
					choice = int(input("\nEnter the number of your choice: "))
					if choice < 1 or choice > len(generators):
						raise ValueError("Invalid choice")
				except ValueError as e:
					print(f"Error: {e}")
					raise Exception("Invalid choice provided")

				selected_label = generators[choice - 1][0]

				final_dir = ""
				for label, generator, dir in generators:
					if label == selected_label:
						selected_generator = generator
						final_dir = dir
						break

			cmd = ["cmake", "-B", "build/" + final_dir, "-G", selected_generator]
			subprocess.run(cmd, check=True)
		except Exception as e:
			print(type(e).__name__ + ":", e)
			print("\nSetup was not completed")
		else:
			print("\nSetup completed!")
			return final_dir

if __name__ == "__main__":
	GenerateBuildFiles()
