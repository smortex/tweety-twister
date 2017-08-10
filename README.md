# testdisk

I have an Adaptec SAS RAID Controller (ASR-3805) that does not present the raw
disks.  I can initialize them using the on-board BIOS, add them to an array in
which each disk is alone (those arrays are "Volumes"), but is the exported disk
visible in the OS the RAW device itself?

Try to find out by writing canaries at the beginning and end of device, and
checking them.

## Usage

The project is built using CMake:

```
cmake -DCMAKE_BUILD_TYPE=Debug .
make
```

Now, write canaries to a disk exposed by the RAID controller (in this example
`/dev/aacd0`):

```
./write-canaries /dev/aacd0
```

Then, access the same drive directly (by connecting it to the system direrctly)
and check the canaries (in this example `/dev/ada5`):


```
./check-canaries /dev/ada5
```
