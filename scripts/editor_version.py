version = -1

with open('src/editor/version.cpp','r') as file:
    for line in file:
        for word in line.split():
            if word.isdigit():
                version = int(word)

if version != -1:
    version += 1

    with open('src/editor/version.cpp', 'w') as file:
        file.write("#include \"version.h\"\n")
        file.write("\n")
        file.write("#define _OMNISCIA_EDITOR_VERSION_ ")
        file.write(str(version) + "\n")
        file.write("\n")
        file.write("unsigned long long get_editor_version() {\n")
        file.write("    return _OMNISCIA_EDITOR_VERSION_;\n")
        file.write("}\n")
        file.write("\n")
    
    print("Editor version: " + str(version))
    exit();
else:
    print("Unable to update editor version")

exit();
