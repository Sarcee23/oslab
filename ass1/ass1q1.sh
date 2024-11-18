# Name : Subhayan Roy Chowdhury
# Roll: 002211001096
# Date: 05/08/2024
# IT UG3 A2
#
# Assignment Details: Assignment 1A: Familiarity with User and System level OS Commands.Run the commands and validate the output
#
# Output details : Gives the brief description about each commmand as well as the output after running them using echo
#
# Compilation command: chmod +x 096_1a.sh; //to give necessary permission to the file
#
# Execution command : ./096_1a.sh
#
# Sample output:
# #Q17 tty
# /dev/pts/22
# /dev/pts/22
# Q18 uname
# Linux
# Linux
# Q19 umask
# 0022
# 0022
# .. and so on


# Q1  who: It displays the information about all the users who have logged into the system currently
echo "#Q1 who"
who
echo "$(who)"

# Q2 whoami: It displays Current username, Terminal number, date and time at which user logged into the system
echo "#Q2 whoami"
whoami
echo "$(whoami)"

# Q3 pwd: It displays current working directory
echo "#Q3 pwd"
pwd
echo "$(pwd)"
# Q4 date: It displays system date and time
echo "#Q4 date"
date
echo "$(date)"

# Q5 ls: It lists the files and directories stored in the current directory
echo "#Q5 ls"
ls
echo "$(ls)"

# Q6 mkdir: It is used to create directories
echo "#Q6 mkdir"
mkdir test_dir
echo "Directory 'test_dir' created"

# Q7 clear: It clears the screen
echo "#Q7 clear"
echo "Screen cleared (not shown in output)"

# Q8 cd: It is used to change the current working directory to any other directory specified
echo "#Q8 cd"
cd test_dir
echo "Changed to directory: $(pwd)"

# Q9 cd..: This command is used to come out from the current working directory
echo "#Q9 cd.."
cd ..
echo "Changed back to: $(pwd)"

# Q10 rmdir: Directories can be deleted using the rmdir command
echo "#Q10 rmdir"
rmdir test_dir
echo "Directory 'test_dir' removed"

# Q11 cat: It displays the contents of a file
echo "#Q11 cat"
echo "Hello, World!" > test_file.txt
cat test_file.txt
echo "$(cat test_file.txt)"

# Q12 cp: It is used to copy a file
echo "#Q12 cp"
cp test_file.txt test_file_copy.txt
echo "File copied"

# Q13 mv: It is used to change the name of a file
echo "#Q13 mv"
mv test_file_copy.txt renamed_file.txt
echo "File renamed"

# Q14 rm: It is used to delete an existing file
echo "#Q14 rm"
rm test_file.txt renamed_file.txt
echo "Files removed"

# Q15 stat: It is used to display file or file system status
echo "#Q15 stat"
touch stat_test_file
stat stat_test_file
echo "$(stat stat_test_file)"
rm stat_test_file

# Q16 stty: Change and print terminal line settings
echo "#Q16 stty -a"
stty -a
echo "$(stty -a)"

# Q17 tty: It prints the filename of the terminal connected to standard input
echo "#Q17 tty"
tty
echo "$(tty)"

# Q18 uname: It prints system information
echo "#Q18 uname"
uname
echo "$(uname)"

# Q19 umask: It specifies user file creation mask
echo "#Q19 umask"
umask
echo "$(umask)"

# Q20 find: It searches for files in a directory hierarchy
echo "#Q20 find"
find . -name "*.txt"
echo "$(find . -name "*.txt")"


# Q21 sort: It sorts the lines of text files
echo "#Q21 sort"
echo -e "c\na\nb" > sort_test.txt
sort sort_test.txt
echo "$(sort sort_test.txt)"
rm sort_test.txt

# Q22 ps: It displays information about the current processes
echo "#Q22 ps"
ps
echo "$(ps)"

# Q23 chmod 777 file1: gives full permission to owner, group and others
echo "#Q23 chmod 777"
touch file1
chmod 777 file1
ls -l file1
echo "$(ls -l file1)"

# Q24 chmod o-w file1: Removes write permission for others
echo "#Q24 chmod o-w"
chmod o-w file1
ls -l file1
echo "$(ls -l file1)"
rm file1he system cannot find the path specified.
