Entrex project  February 21, 2023

The remap script

There is a python script and two files.
The files contain signal renaming rules for
the schematic to which they apply.

Here is how I use this:

1) I clone AJ's repository.

2) This creates the "Trapezoid_Terminal" directory on my system with a bunch of
stuff in it.  Of interest for the remapping business here are two subdirectories
'Interface Board' and  'Processor Board'.

3) I go into each of these directories and copy the schematic file to a file
with the name "proto_sch".  (I do the same for the pcb, creating proto_pcb).
On linux, I type the following commands to do this:

cp 'Entrex Trapezoid Processor Board v37.kicad_sch' proto_sch

cp 'Entrex Trapezoid Processor Board v37.kicad_pcb' proto_pcb

The reason I do this is to keep this as the pristine, never-changing copy of the original schematic
done by AJ.  Every time I rerun the "remap" script, it overwrites the original long filename
(so KiCAD can find it).  I never touch the proto files.

If I was AJ using this program, I would create a copy of the whole project to avoid unhappy mishaps.

4) Once the proto files are made, I place the remap program in the top level directory and
run it from there typing "./remap" on my linux system.

5) On my machine the KiCAD files are on a shared drive visible from Windows where I run KiCAD.
I also play various games with symbolic links.  Windows users can ignore all of this.

------------------------

On 4-26-2023 I wanted to import changes made by AJ, and set up the scheme described
in the Makefile to do this.
