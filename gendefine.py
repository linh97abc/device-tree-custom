import configparser
import hashlib
import sys
import os

out_dir = sys.argv[1]
conf_file = sys.argv[2]

print(f'Generate devicetree:\n  out: {out_dir}\n  conf: {conf_file}')

conf_overlay_file = None
if len(sys.argv) > 3:
    conf_overlay_file = sys.argv[3]
    print(f'  conf_overlay: {conf_overlay_file}')


if not os.path.exists(out_dir):
    os.makedirs(out_dir)

headerFile = os.path.join(out_dir, "devicetree_generated.h")

config = configparser.ConfigParser()
config.read(conf_file)

if conf_overlay_file and os.path.exists(conf_overlay_file):
    config_overlay = configparser.ConfigParser()
    config_overlay.read(conf_overlay_file)

    for section, val in config.items():
        if section in config_overlay:
            val.update(config_overlay[section])

sections = config.sections()
compat_dict = dict()

for devID in sections:
    config_dev = config[devID]
    if 'compatible' not in config_dev:
        continue

    compat = config_dev['compatible']

    if compat not in compat_dict:
        compat_dict[compat] = [config_dev]
    else:
        compat_dict[compat].append(config_dev)

devIDList = list()

genContent = ''

genContent +=('''#ifndef __DEVICETREE_GENERATED_H__
#define __DEVICETREE_GENERATED_H__

''')

if 'default' in config:
    config_default = config['default']

    for key, val in config_default.items():
        genContent += f'#define {key.upper()} {val}\n'

for compat, devs in compat_dict.items():
    i = 0
    genContent += (f"// Device {compat}\n")
    for dev in devs:
        if dev['status'] != 'okay':
            continue
        devID = dev.name.upper()

        if devID not in devIDList: devIDList.append(devID)

        genContent +=(f'#define DT_INST_{i}_{compat}_P_devID {devID}\n')
        genContent +=(f'#define DT_INST_{i}_{compat}_P_name "{devID}"\n')
        for attribue in dev:
            genContent +=(f'#define DT_INST_{i}_{compat}_P_{attribue} {dev[attribue]}\n')
        i += 1
        genContent +=('\n')
    genContent +=(f'#define DT_INST_{compat}_NUM_INSTANCES {i}\n\n')

    fn_list = ' '.join([f'fn({j})' for j in range(i)])
    genContent +=(f'#define DT_FOREACH_OKAY_INST_{compat}(fn) {fn_list}\n\n')

genContent +=("enum DeviceID_t {\n    %s\n};" % ',\n    '.join(devIDList))
genContent +=('\n\n#endif\n')

hash = hashlib.sha1(genContent.encode())

isGenerated = False
try:
    with open(headerFile, 'r') as f:
        content = f.read()
        hashGenerated = hashlib.sha1(content.encode())

        if hash.digest() == hashGenerated.digest():
            print("Device spec has generated")
            isGenerated = True
except:
    pass

if not isGenerated:
    with open(headerFile, 'w') as f:
        f.write(genContent)

    print("Generate devicetree: Done")