import subprocess

import Utils

class WindowConfiguration:
	@classmethod
	def Validate(cls):

		(system, arch) = Utils.GetPlatform()
		if system == "Linux":
			# X11 support
			packages = [
				'libx11-dev',
				'libxrandr-dev',
				'libxinerama-dev',
				'libxcursor-dev',
				'libxi-dev',
				'libxft-dev',
				'libxcomposite-dev',
				'libxdamage-dev'
			]

			try:
				subprocess.run(['sudo', 'apt', 'install', '-y'] + packages, check=True)
				return True
			except:
				return False

		else:
			print("Done")
			return True
