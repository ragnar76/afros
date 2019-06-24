#!/bin/sh

TMPFILE="/tmp/amail_book.tmp"
BACKUPFILE="/tmp/amail_book.bak"

cat /dev/null > /$TMPFILE

GetRecordNR () {

	awk -v ENR="$1" \
	'{
	if ( $0 ~ "Username = " ){
		RECNR = RECNR+1
		if(RECNR == ENR ){
			print $0
			getline
			while ($0 !~ "Username = " && FNR != OLDFNR ){
				OLDFNR=FNR
				print $0
				getline
			}
		}
	}
	}' $BOOKFILE

}

SortList () {
	REC=0
	while [ $REC -lt $NOR ]; do
		REC=`expr $REC + 1`
		VALUE=`GetRecordNR $REC | grep "$SEARCH1" | cut -c $SERACH_SIZE1-`
		if [ "$VALUE" = "" ]; then
			VALUE="ZZZ"
		fi
		
		if [ "$SEARCH2" != "" ]; then
			VALUE2=`GetRecordNR $REC | grep "$SEARCH2" | cut -c $SERACH_SIZE2-`
			if [ "$VALUE2" != "" ]; then
				VALUE=`echo $VALUE "$VALUE2"`
			fi
		fi
		printf "%s\t%s\n"  "$REC" "$VALUE"
	done
}


if [ $# -lt 1 ]; then
	echo "Usage: "
	echo " " $0 " [Key1] [Key2]"
	echo "  Keys:"
	printf "\tUsername\n\tEmail\n\tNickname\n\tComment[1-3]\n\n"
	echo
	echo "Using defaults"
	SBY1="Username"
else
	SBY1=$1
fi
SEARCH1=`printf "%s = " $SBY1` 
SERACH_SIZE1=`echo $SEARCH1 | wc -c`

if [ $# = 2 ]; then
	SBY2=$2
	SEARCH2=`printf "%s = " $SBY2` 
	SERACH_SIZE2=`echo $SEARCH2 | wc -c`
else
	SBY2=""
	SEARCH2=""
	SERACH_SIZE2=""
fi

if [ -r $HOME/defaults/amail.book ]; then
	BOOKFILE=$HOME/defaults/amail.book
else
	if [ -r $HOME/amail.book ]; then
		BOOKFILE=$HOME/amail.book
	else
		echo "Cannont find amail.book"
		echo -n "specify: "
		read BOOKFILE
	fi
fi
	


echo "Sorting" $BOOKFILE "by" $SBY1 $SBY2"."

NOR=`grep "Username = " $BOOKFILE | wc -l`
echo $NOR "records found."

echo "Sorting ..."
NORDER=`SortList | sort +1 | cut -f 1`
echo -n "Saving "
for REC in $NORDER
do
	echo -n "."
	GetRecordNR $REC >> $TMPFILE
done

echo
echo " Sorted adressbook is now in $TMPFILE"
echo -n " Replace original archive ? (y/N) "
read AN
if [ "$AN" = "y" ]; then
	cp $BOOKFILE $BACKUPFILE
	echo
	echo " Original adress book is in $BACKUPFILE"
	cp $TMPFILE $BOOKFILE
fi
echo
