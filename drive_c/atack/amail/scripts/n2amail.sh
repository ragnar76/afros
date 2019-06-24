#!/bin/sh


#####################################################################
HaveFrom (){
	if [ -z "`head -1 $1 | awk '{ print $1 }' | grep from`" ]; then
		echo >> $AMAILBOX
		echo "From n2aMail " `date "+%a %b %d %X %Y"` >> $AMAILBOX
	fi
}

#####################################################################
CheckPath(){
	A="n"
	while [ "$A" = "n" ]
	do
		echo "  Newsie mail-boxfile : " $NEWSIEBOX
		echo "  amail mbox file     : " $AMAILBOX
		echo
		echo -n "Correct? (y/n)"
		read	A
		if [ "$A" = "n" ]; then
			echo -n "   Newsie mail-box file: "
			read NEWSIEBOX
			if [ ! -f $NEWSIEBOX ]; then
				echo
				echo "   \"$NEWSIEBOX\" does not exist!"
				echo
				exit
			fi
			echo -n "   amail mbox file     : "
			read AMAILBOX
			echo; echo
		fi
	done
	if [ -z "$NEWSIEBOX" ]; then
		exit
	fi
}
#####################################################################
# Start
#
	NEWSIEBOX="/d/communic/newsie/mail/inbox.mbx"
	AMAILBOX=`awk -F = '/InBoxPath/ { print $2 } ' $HOME/amail.cfg`

if [ $# -eq 1 ]; then
	NEWSIEBOX=$1
fi

if [ $# -eq 2 ]; then
	NEWSIEBOX=$1
	AMAILBOX=$2
fi

echo
echo " NEWSiE to amail mailbox convertor "
echo "-----------------------------------"
echo
echo "Usage:"
echo "          ./n2amail.sh [newsie_box_file] [amail_mbox_file]"
echo "---"
echo

CheckPath

LIST=`awk -F '\t' '{ printf("%s\n", $6) }' $NEWSIEBOX`

for MAIL in $LIST
do
	if [ -f $MAIL ]; then
		echo $MAIL
		HaveFrom $MAIL
		cat $MAIL | tr -d '\r' >> $AMAILBOX
	fi
done
