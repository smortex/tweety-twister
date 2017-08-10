# testdisk

I have an Adaptec SAS RAID Controller (ASR-3805) that does not present the raw
disks.  I can initialize them using the on-board BIOS, add them to an array in
which each disk is alone (those arrays are "Volumes"), but is the exported disk
visible in the OS the RAW device itself?

Try to find out by writing canaries at the beginning and end of device, and
checking them.
