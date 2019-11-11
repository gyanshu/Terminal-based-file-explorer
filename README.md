crusher@crusher-HP-Pavilion-15-Notebook-PC:~/Terminal-based-file-explorer$ git config credential.helper store
crusher@crusher-HP-Pavilion-15-Notebook-PC:~/Terminal-based-file-explorer$ 
# Terminal-based-file-explorer
This File explorer works in two modes. The application would start in
normal mode, which is the default mode and can be used to explore the current directory
and navigate around in the filesystem.
The root of the application wil be the directory where the application was
started.
The last line of the display screen shows the status bar(normal mode/command mode).

## Normal Mode:
    1. The file explorer reads and displays list of files and directories in the current folder-
        1. It shows each file(dirctories too) in the directory. The following attributes are mentioned for each file:
            1. Ownership (User & Group) & Permissions
            2. File size (in bytes)
            3. Last modified
            4. File name
        2. The application also shows the entries “.” & “..” for current and
        parent directory respectively.
        2. A File or directory can be opened upon pressing enter key.
        3. Navigation:
            1. Go back: On pressing left arrow key the explorer goes back to
               the previously visited directory if any.
            2. Go forward: On pressing right arrow key the explorer goes
               forward to the next directory (Similar to forward/back feature of web
               pages).
            3. Up one level: On pressing backspace it goes one level up in the directory structure.
            4. Home: On pressing ‘h’ key, it goes to the home folder (the folder where
               application was started).
