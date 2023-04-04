version = -1

with open('editor/version.h','r') as file:
    for line in file:
        for word in line.split():
            if word.isdigit():
                version = int(word)

if version != -1:
    version += 1

    with open('editor/version.h', 'w') as file:
        file.write("#ifndef _OMNISCIA_EDITOR_VERSION_H_\n")
        file.write("#define _OMNISCIA_EDITOR_VERSION_H_\n")
        file.write("\n")
        file.write("#define _OMNISCIA_EDITOR_VERSION_ ")
        file.write(str(version) + "\n")
        file.write("\n")
        file.write("#endif\n")
    
    print("Editor version: " + str(version))
    exit();
else:
    print("Unable to update editor version")

exit();
