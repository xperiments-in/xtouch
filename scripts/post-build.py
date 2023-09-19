import json
import subprocess
import os
Import("env")

env = DefaultEnvironment()


def delete_bin_files(directory):
    try:
        for filename in os.listdir(directory):
            if filename.endswith(".bin"):
                file_path = os.path.join(directory, filename)
                os.remove(file_path)
                print(f"Deleted: {file_path}")
        print("All .bin files deleted successfully.")
    except Exception as e:
        print(f"An error occurred: {str(e)}")


def post_build_increment_semver(json_file, bump_type="patch"):
    # Load the JSON from the file
    with open(json_file, 'r') as f:
        data = json.load(f)

    # Get the current version from the JSON
    version = data.get("version", "0.0.1").split(".")

    # Increment the version based on the bump type (major, minor, or patch)
    if bump_type == "major":
        version[0] = str(int(version[0]) + 1)
        version[1] = "0"
        version[2] = "0"
    elif bump_type == "minor":
        version[1] = str(int(version[1]) + 1)
        version[2] = "0"
    elif bump_type == "patch":
        version[2] = str(int(version[2]) + 1)
    else:
        raise ValueError("Bump type must be 'major', 'minor', or 'patch'.")

    # Update the version in the JSON
    data["version"] = ".".join(version)

    # Save the updated JSON to the file
    with open(json_file, 'w') as f:
        json.dump(data, f, indent=2)


def post_build_ota(version_value):

    ota = {
        "version": version_value,
        "url": f"http://retroconsol.es/products/p1touch/ota/p1touch.{version_value}.bin"
    }

    # Serialize the webusb_manifest as a JSON string
    ota_serialized = json.dumps(ota, indent=2)

    # If you want to save it to a file, you can do:
    with open("ota/ota.json", "w") as ota_file:
        ota_file.write(ota_serialized)


def post_build_manifest(version_value):

    webusb_manifest_fw_path = f"p1touch.web.{version_value}.bin"

    # Create a new JSON object with the updated version and path values
    webusb_manifest = {
        "name": "P1Touch",
        "version": version_value,
        "new_install_prompt_erase": True,
        "builds": [
            {
                "chipFamily": "ESP32",
                "parts": [{"path": webusb_manifest_fw_path, "offset": 0}]
            }
        ]
    }

    # Serialize the webusb_manifest as a JSON string
    webusb_manifest_serialized = json.dumps(webusb_manifest, indent=2)

    # If you want to save it to a file, you can do:
    with open("webusb/webusb.manifest.json", "w") as webusb_manifest_file:
        webusb_manifest_file.write(webusb_manifest_serialized)


def post_build_merge_bin(version):
    ota_bin_source = ".pio/build/esp32dev/firmware.bin"
    ota_bin_target = f"./ota/p1touch.{version}.bin"
    subprocess.run(['cp', ota_bin_source, ota_bin_target])

    web_usb_fw = f"../../../webusb/p1touch.web.{version}.bin"
    esptool_cmd = [
        'esptool.py',
        '--chip', 'ESP32',
        'merge_bin',
        '-o', web_usb_fw,
        '--flash_mode', 'dio',
        '--flash_size', '4MB',
        '0x1000', 'bootloader.bin',
        '0x8000', 'partitions.bin',
        '0x10000', 'firmware.bin'
    ]

    subprocess.run(esptool_cmd, cwd="./.pio/build/esp32dev")


def post_build_action(source, target, env):

    with open("version.json", "r") as version_file:
        version_data = json.load(version_file)
        version_value = version_data.get("version", "UNKNOWN")

    delete_bin_files("./ota")
    delete_bin_files("./webusb")
    post_build_manifest(version_value)
    post_build_ota(version_value)
    post_build_merge_bin(version_value)

    post_build_increment_semver("version.json", bump_type="patch")


env.AddPostAction("buildprog", post_build_action)
