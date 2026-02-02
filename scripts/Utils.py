import sys
import os
import platform

import requests
import time
import urllib

from zipfile import ZipFile
import tarfile

def GetPlatform():
	# System
	system = platform.system()
	if system not in ("Windows", "Linux", "Darwin"):
		system = None
	if system == "Darwin":
		system = "MacOSX"

	# Architecture
	mach = platform.machine().lower()
	if mach in ("x86_64", "amd64"):
		arch = "x86_64"
	elif mach in ("i386", "i686"):
		arch = "x86"
	elif mach in ("arm64", "aarch64", "armv7l", "armv6l"):
		arch = mach
	else:
		arch = None

	if system == None or arch == None:
		return "Unknown"

	return (system, arch)

def DownloadFile(url, filepath):
	path = filepath
	filepath = os.path.abspath(filepath)
	os.makedirs(os.path.dirname(filepath), exist_ok=True)

	if (type(url) is list):
		for url_option in url:
			print("Downloading", url_option)
			try:
				DownloadFile(url_option, filepath)
				return
			except urllib.error.URLError as e:
				print(f"URL Error encountered: {e.reason}. Proceeding with backup...\n\n")
				os.remove(filepath)
				pass
			except urllib.error.HTTPError as e:
				print(f"HTTP Error  encountered: {e.code}. Proceeding with backup...\n\n")
				os.remove(filepath)
				pass
			except:
				print(f"Something went wrong. Proceeding with backup...\n\n")
				os.remove(filepath)
				pass
		raise ValueError(f"Failed to download {filepath}")
	if not(type(url) is str):
		raise TypeError("Argument 'url' must be of type list or string")

	with open(filepath, 'wb') as f:
		headers = {'User-Agent': "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_4) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/83.0.4103.97 Safari/537.36"}
		response = requests.get(url, headers=headers, stream=True)
		total = response.headers.get('content-length')

		if total is None:
			f.write(response.content)
		else:
			downloaded = 0
			total = int(total)
			startTime = time.time()
			for data in response.iter_content(chunk_size=max(int(total/1000), 1024*1024)):
				downloaded += len(data)
				f.write(data)
				
				try:
					done = int(50*downloaded/total) if downloaded < total else 50
					percentage = (downloaded / total) * 100 if downloaded < total else 100
				except ZeroDivisionError:
					done = 50
					percentage = 100
				elapsedTime = time.time() - startTime
				try:
					avgKBPerSecond = (downloaded / 1024) / elapsedTime
				except ZeroDivisionError:
					avgKBPerSecond = 0.0

				avgSpeedString = '{:.2f} KB/s'.format(avgKBPerSecond)
				if (avgKBPerSecond > 1024):
					avgMBPerSecond = avgKBPerSecond / 1024
					avgSpeedString = '{:.2f} MB/s'.format(avgMBPerSecond)
				sys.stdout.write('\r[{}{}] {:.2f}% ({})	 '.format('█' * done, '.' * (50-done), percentage, avgSpeedString))
				sys.stdout.flush()
	sys.stdout.write('\n')

def UnzipFile(filepath, deleteZipFile=True):
	zipFilePath = os.path.abspath(filepath) # get full path of files
	zipFileLocation = os.path.dirname(zipFilePath)

	zipFileContent = dict()
	zipFileContentSize = 0
	with ZipFile(zipFilePath, 'r') as zipFileFolder:
		for name in zipFileFolder.namelist():
			zipFileContent[name] = zipFileFolder.getinfo(name).file_size
		zipFileContentSize = sum(zipFileContent.values())
		extractedContentSize = 0
		startTime = time.time()
		for zippedFileName, zippedFileSize in zipFileContent.items():
			UnzippedFilePath = os.path.abspath(f"{zipFileLocation}/{zippedFileName}")
			os.makedirs(os.path.dirname(UnzippedFilePath), exist_ok=True)
			if os.path.isfile(UnzippedFilePath):
				zipFileContentSize -= zippedFileSize
			else:
				zipFileFolder.extract(zippedFileName, path=zipFileLocation, pwd=None)
				extractedContentSize += zippedFileSize
			try:
				done = int(50*extractedContentSize/zipFileContentSize)
				percentage = (extractedContentSize / zipFileContentSize) * 100
			except ZeroDivisionError:
				done = 50
				percentage = 100
			elapsedTime = time.time() - startTime
			try:
				avgKBPerSecond = (extractedContentSize / 1024) / elapsedTime
			except ZeroDivisionError:
				avgKBPerSecond = 0.0
			avgSpeedString = '{:.2f} KB/s'.format(avgKBPerSecond)
			if (avgKBPerSecond > 1024):
				avgMBPerSecond = avgKBPerSecond / 1024
				avgSpeedString = '{:.2f} MB/s'.format(avgMBPerSecond)
			sys.stdout.write('\r[{}{}] {:.2f}% ({})	 '.format('█' * done, '.' * (50-done), percentage, avgSpeedString))
			sys.stdout.flush()
	sys.stdout.write('\n')

	if deleteZipFile:
		os.remove(zipFilePath) # delete zip file

def UntarXZFile(filepath, deleteTarFile=True):
	tarFilePath = os.path.abspath(filepath)
	tarFileLocation = os.path.dirname(tarFilePath)

	tarFileContent = {}
	tarFileContentSize = 0

	with tarfile.open(tarFilePath, mode="r:xz") as tar:
		for member in tar.getmembers():
			if member.isfile():
				tarFileContent[member] = member.size

		tarFileContentSize = sum(tarFileContent.values())
		extractedContentSize = 0
		startTime = time.time()

		for member, memberSize in tarFileContent.items():
			extractedPath = os.path.abspath(
				os.path.join(tarFileLocation, member.name)
			)
			os.makedirs(os.path.dirname(extractedPath), exist_ok=True)

			if os.path.isfile(extractedPath):
				tarFileContentSize -= memberSize
			else:
				tar.extract(member, path=tarFileLocation)
				extractedContentSize += memberSize

			try:
				done = int(50 * extractedContentSize / tarFileContentSize)
				percentage = (extractedContentSize / tarFileContentSize) * 100
			except ZeroDivisionError:
				done = 50
				percentage = 100

			elapsedTime = time.time() - startTime
			try:
				avgKBPerSecond = (extractedContentSize / 1024) / elapsedTime
			except ZeroDivisionError:
				avgKBPerSecond = 0.0

			avgSpeedString = f"{avgKBPerSecond:.2f} KB/s"
			if avgKBPerSecond > 1024:
				avgSpeedString = f"{avgKBPerSecond / 1024:.2f} MB/s"

			sys.stdout.write(
				f"\r[{'█' * done}{'.' * (50 - done)}] {percentage:.2f}% ({avgSpeedString})  "
			)
			sys.stdout.flush()

	sys.stdout.write("\n")

	if deleteTarFile:
		os.remove(tarFilePath)
