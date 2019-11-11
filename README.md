# Terminal-based-file-explorer
A functional terminal based file explorer, albeit with a restricted feature set.
The application would start in the Normal mode, which is the default mode and can be used to explore the current directory and navigate around in the filesystem.
In Command Mode you can do basic file opertions like move, rename, delete, etc.
The root of the application wil be the directory where the application was
started.
The last line of the display screen shows the status bar(normal mode/command mode).
## Functionality
## Normal Mode:
    1. The file explorer reads and displays list of files and directories in the current folder-
        1. It shows each file(dirctories too) in the directory. The following attributes are mentioned for each file:
            1. Ownership (User & Group) & Permissions
            2. File size (in bytes)
            3. Last modified
            4. File name
        2. The application also shows the entries “.” & “..” for current and
        parent directory respectively.
        3. A File or directory can be opened upon pressing enter key.
        4. Navigation:
            1. Go back: On pressing left arrow key the explorer goes back to
               the previously visited directory if any.
            2. Go forward: On pressing right arrow key the explorer goes
               forward to the next directory (Similar to forward/back feature of web
               pages).
            3. Up one level: On pressing backspace it goes one level up in the directory structure.
            4. Home: On pressing ‘h’ key, it goes to the home folder (the folder where
               application was started).

## Command Mode:
    The application enters the command mode whenever the “:” (colon) key is pressed. Upon entering the command mode the user is able to enter different commands. All commands appear in a bottom status bar.

    Command list:
    1. Move: ‘move <source_file(s)> <destination_directory>’
        1. Ex: move foo.txt bar.txt ~/foobar
        2. You can also move directories.
        
    2. Rename: ‘rename <old_filename> <new_filename>’
        Ex: rename foo.txt bar.txt
        
    3. Create file: ‘create_file <file_name> <destination_path>’
       Create directory ‘create_dir <dir_name> <destination_path>’
        Ex: create_file foo.txt ~/foobar
        Ex: create_file foo.txt .
        Ex: create_dir folder_name ~/foobar
        
    4. Delete file: ‘delete_file <file_path>’
       Delete directory: ‘delete_dir <directory_path>’
        Ex: delete_file superbad.mp4
        Ex: delete_directory ~/Downloads/Project
     
    5. Goto: 'goto <location>'
        Ex: goto ~/Documents
    
    6. Snapshotting the filesystem and dumping into a file: ‘snapshot <folder> <dumpfile>’
        Given a base directory this command recursively crawls the
        directory and stores the output in the dumpfile.
     
    7. On pressing ‘ESC’ key the application goes back to Normal Mode.

## Installation instructions
```git clone 'https://github.com/gyanshu/Terminal-based-file-explorer
cd Terminal-based-file-explorer
make
```
Now go to the directory which you want to make the root and execute the executable file "driver" to start the application.
`./<path_to_driver_parent>/driver`

Enjoy!


    
    
 
