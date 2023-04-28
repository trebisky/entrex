# Makefile 4-26-2023
#
# I need to keep both Entrex and Entrex.pristine for the following reason.
# I have made many changes in "Entrex" and git won't let me pull changes
# into here until I push my changes, which I cannot do.
#
# So I do this:
#
# git clone https://github.com/ForgottenMachines/Entrex.git Entrex.pristine
#
# This takes (took) a long time the first time because of all the backups,
# manuals, etc.  Doing a pull/update in the future will go much faster.
#
# So, what do I do once I have new stuff in "pristine"
#
#    cd Entrex/Trapezoid_Terminal
#    make update


PRISTINE = ../../Entrex.pristine/Trapezoid_Terminal

PRO = '$(PRISTINE)/Processor Board'
CUR_PRO = './Processor Board'

INT = '$(PRISTINE)/Interface Board'
CUR_INT = './Interface Board'

all:
	echo "Sorry"

plist:
	cd $(CUR_PRO) ; ls -l
	cd $(PRO) ; ls -l
	cd $(CUR_INT) ; ls -l
	cd $(INT) ; ls -l

setup:
	ln -s /u1/Projects/Anthrax/Github/remap/remap
	ln -s /u1/Projects/Anthrax/Github/remap/interface_remap
	ln -s /u1/Projects/Anthrax/Github/remap/processor_remap
	cd $(CUR_INT); mv 'Entrex Trapezoid Interface Board v23.kicad_pcb' proto_pcb
	cd $(CUR_INT); mv 'Entrex Trapezoid Interface Board v23.kicad_sch' proto_sch
	cd $(CUR_INT); ln -s 'Entrex Trapezoid Interface Board v23.kicad_sch' new_sch
	cd $(CUR_PRO); mv 'Entrex Trapezoid Processor Board v37.kicad_pcb' proto_pcb
	cd $(CUR_PRO); mv 'Entrex Trapezoid Processor Board v37.kicad_sch' proto_sch
	cd $(CUR_PRO); ln -s 'Entrex Trapezoid Processor Board v37.kicad_sch' new_sch

map:
	./remap

# Old scheme to copy files from pristine github clone
update:
	cp $(PRO)/'Entrex Trapezoid Processor Board v37.kicad_pcb' $(CUR_PRO)/proto_pcb
	cp $(PRO)/'Entrex Trapezoid Processor Board v37.kicad_sch' $(CUR_PRO)/proto_sch
	cp $(INT)/'Entrex Trapezoid Interface Board v23.kicad_pcb' $(CUR_INT)/proto_pcb
	cp $(INT)/'Entrex Trapezoid Interface Board v23.kicad_sch' $(CUR_INT)/proto_sch
