#include <stdio.h>
#include <dirent.h>

#include "sw.h"
#include "sstr.h"


int main()
{
    char path[255] = {0};
    getcwd(path, 255);

    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(path)) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            $ entry = $from(ent->d_name);
            $ fullPath = $append_fmt(path, "\\%s", ent->d_name);

            DWORD attributes = GetFileAttributesA(fullPath);
            if (attributes != INVALID_FILE_ATTRIBUTES)
            {
                if (attributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    entry = $insert(fullPath, 0, "#| ");
                }
                else
                {
                    entry = $insert(fullPath, 0, "F| ");
                }
            }

            printf("%s\n", entry);
        }
        closedir(dir);
    }
    else
    {
        /* could not open directory */
        perror("");
        return EXIT_FAILURE;
    }

    return 1;
}
