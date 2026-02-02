import os
import platform
import subprocess
import shutil

import Utils

class CMakeConfiguration:
	installCMakeVersion = "4.2.1"
	cmakeDirectory = "./vendor"

	@classmethod
	def Validate(cls):
		if (not cls.CheckIfCMakeInstalled()):
			return False
		return True

	@classmethod
	def CheckIfCMakeInstalled(cls):
		try:
			output = subprocess.check_output(["cmake", "--version"], stderr=subprocess.STDOUT, text=True)
			first, second, version = output.splitlines()[0].split(" ")# Show first line
			print(f"CMake {version} is installed")
			return True
		except FileNotFoundError:
			print("CMake is not installed")
		except subprocess.CalledProcessError:
			print("CMake was found, but could be corrupted")

		cls.__InstallCMake()

		return False

	@classmethod
	def __InstallCMake(cls):
		permissionGranted = False
		while not permissionGranted:
			if platform.system() == "Linux":
				reply = str(input("Would you like to install CMake? [Y/N]: "))
			else:
				reply = str(input("Would you like to install CMake {0:s}? [Y/N]: ".format(cls.installCMakeVersion))).lower().strip()[:1]
			if reply == 'n' or reply == 'N':
				return
			permissionGranted = (reply == 'y' or reply == 'Y')

		(system, arch) = Utils.GetPlatform()
		cmakeDir = cls.cmakeDirectory
		version = cls.installCMakeVersion

		# Windows
		if system == "Windows":
			if arch == "x86_64":
				cmakeInstallURL = f"https://github.com/Kitware/CMake/releases/download/v{version}/cmake-{version}-windows-x86_64.msi"
				cmakePath = os.path.join(cmakeDir, f"cmake-{version}-x86_64-installer.exe")
			if arch == "x86":
				cmakeInstallURL = f"https://github.com/Kitware/CMake/releases/download/v{version}/cmake-{version}-windows-i386.msi"
				cmakePath = os.path.join(cmakeDir, f"cmake-{version}-x86-installer.exe")
			if arch == "arm64":
				cmakeInstallURL = f"https://github.com/Kitware/CMake/releases/download/v{version}/cmake-{version}-windows-arm64.msi"
				cmakePath = os.path.join(cmakeDir, f"cmake-{version}-arm64-installer.exe")
		# Linux
		elif system == "Linux":
			pass
		# MacOSX
		elif system == "MacOSX":
			cmakeInstallURL = f"https://github.com/Kitware/CMake/releases/download/v{version}/cmake-{version}-macos10.10-universal.dmg"
			cmakePath = os.path.join(cmakeDir, f"cmake-{version}-universal-installer.dmg")
		else:
			print(f"{system}-{arch} not supported for automatic installation")
			return

		if system != "Linux":
			print("Downloading {0:s} to {1:s}".format(cmakeInstallURL, cmakePath))
			Utils.DownloadFile(cmakeInstallURL, cmakePath)

		if system == "Windows":
			print("Running CMake installer...")
			os.startfile(os.path.abspath(cmakePath))
		elif system == "Linux":
			import distro # type: ignore
			if distro.id() in ("ubuntu", "debian", "raspbian", "raspios"):
				print("Running apt to install CMake...")
				subprocess.run(["sudo", "apt", "update"], check=True)
				subprocess.run(["sudo", "apt", "install", "-y", "cmake"], check=True)
			elif distro.id() in ("fedora", "centos", "rhel"):
				print("Running dnf to install CMake...")
				subprocess.run(["sudo", "dnf", "install", "-y", "cmake"], check=True)
			elif distro.id() in ("arch", "manjaro"):
				print("Running pacman to install CMake...")
				subprocess.run(["sudo", "pacman", "-Sy", "--noconfirm", "cmake"], check=True)
			else:
				print(f"{distro.name()} is not supported for automatic installation")
		elif system == "MacOSX":
			print("Running CMake installer...")
			subprocess.run(["chmod", "+x", cmakePath])
			subprocess.run(["hdiutil", "attach", cmakePath, "-nobrowse", "-quiet"], check=True)
			app_path = "/Applications/CMake.app"
			if os.path.exists(app_path):
				shutil.rmtree(app_path)
			subprocess.run(["cp", "-R", f"/Volumes/cmake-{version}-macos10.10-universal/CMake.app", "/Applications/"], check=True)
			subprocess.run(["hdiutil", "detach", f"/Volumes/cmake-{version}-macos10.10-universal", "-quiet"], check=True)
			subprocess.run(["sudo", "/Applications/CMake.app/Contents/bin/cmake-gui", "--install"], check=True)
			print(f"CMake {version} has been installed")

		else:
			print("Cannot execute the installation automatically")
			print(f"Execute the installation manually (installer is located at \"{os.path.abspath(cmakeDir)}\")")
		print("Re-run this script after installation!")
		quit()
