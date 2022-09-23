#Vaishnavi Desai
#analyze_txt.sh
#to analyze given text file

#!/bin/bash

if [ ! -f $1 ]
then
	echo "File does not exist"
else 
	if [ -f 1.txt ] || [ -f 2.txt ] || [ -f 3.txt ] || [ -f 4.txt ] || [ -f 5.txt ] || [ -f 6.txt ]
	then 
	rm 1.txt 
	rm 2.txt 
	rm 3.txt 
	rm 4.txt 
	rm 5.txt 
	rm 6.txt 
	fi 
			
	echo "$( cat t.txt |tr 'A-Z' 'a-z' | tr '[:punct:]' '\n' | tr '-' '\n'| tr '[:blank:]' '\n' |sort -f |uniq -ic)"  >> 1.txt
	
	
	 echo "$( cat $1 |tr 'A-Z' 'a-z' | tr '[:punct:]' '\n' | tr '[:blank:] ' '\n' | sort | grep '\w*th\b' |uniq -ic)" >> 2.txt

	
	 echo "$( cat $1 |tr 'A-Z' 'a-z' | tr '[:punct:]' '\n' | tr '[:blank:] ' '\n' | sort | grep '\bth\w*' |uniq -ic)" >> 3.txt
	 
		 
	 echo "$( cat $1 | sort | grep "[A-Z]" |tr 'A-Z' 'a-z' | uniq -ic )" >> 4.txt
	 
	 head -5 $1 >> 5.txt
	 
	 tail -7 $1 >> 6.txt
	 
fi



