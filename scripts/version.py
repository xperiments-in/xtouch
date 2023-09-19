import json
data = json.load(open('version.json'))
print(f"-D XTOUCH_FIRMWARE_VERSION=\\\"{data['version']}\\\"")
