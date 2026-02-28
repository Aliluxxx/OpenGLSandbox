import subprocess
import platform
import sys
import importlib.util as importlib_util

class PythonConfiguration:
	@classmethod
	def Validate(cls):
		if not cls.__ValidatePython():
			return False # Cannot validate further

		# General packages
		for packageName in ["requests"]:
			if not cls.__ValidatePackage(packageName):
				return False # Cannot validate further

		# Windows specific packages
		if platform.system() == "Windows":
			for packageName in ["inquirer"]:
				if not cls.__ValidatePackage(packageName):
					return False # Cannot validate further

		# Linux specific packages
		if platform.system() == "Linux":
			for packageName in ["distro"]:
				if not cls.__ValidatePackage(packageName):
					return False # Cannot validate further

		return True

	@classmethod
	def __ValidatePython(cls, versionMaj = 3, versionMin = 3):
		if sys.version is not None:
			print("Python version {0:d}.{1:d}.{2:d} detected.".format( \
				sys.version_info.major, sys.version_info.minor, sys.version_info.micro))
			if sys.version_info.major < versionMaj or (sys.version_info.major == versionMaj and sys.version_info.minor < versionMin):
				print("Python version too low, expected version {0:d}.{1:d} or higher.".format( \
					versionMaj, versionMin))
				return False
			return True
		print("Python system verion in None")
		return False

	@classmethod
	def __ValidatePackage(cls, packageName):
		if importlib_util.find_spec(packageName) is None:
			return cls.__InstallPackage(packageName)
		return True

	@classmethod
	def __InstallPackage(cls, packageName):
		permissionGranted = False
		while not permissionGranted:
			reply = str(input("Would you like to install Python package '{0:s}'? [Y/N]: ".format(packageName.replace("_", "-")))).lower().strip()[:1]
			if reply == 'n' or reply == 'N':
				return False
			permissionGranted = (reply == 'y' or reply == 'Y')
		
		print(f"Installing {packageName.replace('_', '-')} module...")
		if platform.system() == "Windows":
			subprocess.check_call(['python', '-m', 'pip', 'install', packageName.replace("_", "-")])
		else:
			subprocess.check_call(['python3', '-m', 'pip', 'install', packageName.replace("_", "-")])

		return cls.__ValidatePackage(packageName)

if __name__ == "__main__":
	PythonConfiguration.Validate()
