import platform
import subprocess

from Setup import GenerateBuildFiles

def CompileBuildFiles():
	selected_generator = GenerateBuildFiles()
	if selected_generator is not None:

		configurations = ["Debug", "Release", "Dist"]

		if platform.system() == "Windows":
			import inquirer

			question = [
				inquirer.List(
					"configuration",
					message="Choose a configuration",
					choices=configurations,
					carousel=True
				)
			]

			answer = inquirer.prompt(question)
			selected_label = answer["configuration"]

			selected_config = ""
			for config in configurations:
				if config == selected_label:
					selected_config = config
					break
		else:
			print("\nChoose a build system:")
			for idx, config in enumerate(configurations, 1):
				print(f"{idx}. {config}")

			try:
				choice = int(input("\nEnter the number of your choice: "))
				if choice < 1 or choice > len(configurations):
					raise ValueError("Invalid choice")
			except ValueError as e:
				print(f"Error: {e}")
				raise Exception("Invalid choice provided")

			selected_label = configurations[choice - 1][0]

			selected_config = ""
			for config in configurations:
				if config == selected_label:
					selected_config = config
					break

		print(f"\nCompiling for {selected_generator}-{selected_config}...")
		try:
			subprocess.run(["cmake", "--build", f"build/{selected_generator}", "--config", f"{selected_config}"], check=True)
		except Exception as e:
			print(type(e).__name__ + ":", e)
			print("\nCompilation failed")
		else:
			print("\nCompilation succeeded!")
			return (selected_generator, selected_config)

if __name__ == "__main__":
	CompileBuildFiles()
