version = -1

with open('src/version.h','r') as file:
    for line in file:
        for word in line.split():
            if word.isdigit():
                version = int(word)

if version != -1:
    version += 1

    with open('src/version.h', 'w') as file:
        file.write("#ifndef _OMNISCIA_VERSION_H_\n")
        file.write("#define _OMNISCIA_VERSION_H_\n")
        file.write("\n")
        file.write("#define _OMNISCIA_VERSION_ ")
        file.write(str(version) + "\n")
        file.write("\n")
        file.write("#endif\n")
    
    print("Game version: " + str(version))
    exit();
else:
    print("Unable to update src version")

exit();
