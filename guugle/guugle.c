/*author Wolfgang Gerlach
Projektseminar bei Robert Giegerich
implementation of "guugle" in C*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define NEW_LIST_ELEMENT(x) x=(struct listElement *) malloc(sizeof(struct listElement));x->next=NULL;x->pos=-1

#define NEW_LIST(x) x=(struct list *) malloc(sizeof(struct list));x->begin=NULL;x->end=NULL


//Attention: Some Arrays contain in the first field the position of the last element.


 //fasta: http://ngfnblast.gbf.de/docs/fasta.html
 // Hauptalgorithmus: iterative Anwendung der Funktion "nextLevel"
 
 // a, g, c, u, #
 
// a=1100 00 1
// c=1100 01 1
// g=1100 11 1
// u=1110 10 1

//Declaration functions
struct list * 				stringToList();
struct sequenceContainer * 	parseFile(char *);
int 						isComplement(char a, char b);	
char * 						getDescription(struct sequenceContainer *cont, int descr);
int * countingSort(int depth, int * suffixArray, char * seq, int l, int r);
int * getSuffixNumbers(struct sequenceContainer * cont);


//Declaration struct
struct match {	int distance;
				int target;
				int query;
				struct match *nextMatch;
};

struct matchList {	struct match *firstMatch;
					struct match *lastMatch;
};

struct sequenceContainer {	int descriptionLengthTotal; //TODO brauch ich das noch ?
							int sequenceLengthTotal;
							int numberOfSequences;
							char *sequence; // descr\nacgt>descr\nacgt...
							int *descPos;
							int *sequPos;
						};
struct listElement	{ 		int pos;			//suffix startposition
							struct listElement *next;	//next list element
					};
struct list {				struct listElement *begin;
							struct listElement *end; //stored for concatenation of 2 lists.
			};
			
//a,c,u,g,n : a-u, c-g, g-u, #, n
//Matrix: a,g,c,u,n,#			
int compl[6][6]={{0,0,0,1,0,0},{0,0,1,1,0,0},{0,1,0,0,0,0},{1,1,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
int * count;
	
int * toNum;
int matchNumber=0;
int	maxMatchNumber=-1;
int minMatchLength = -1;	
int extendSeed = -1;	
int statflag = 0;
int statmax=1000;
	
struct sequenceContainer *seqSetA,*seqSetB;				
				
int main (int argc, char* argv[])
{
	
	int refList,i;
	char *fileA,*fileB;
	fileA = NULL;
	fileB = NULL;
	int c;
	int dflag, errorflag, index;
	dflag = 0;
	statflag = 0;
	errorflag = 0;
	char *darg;
	char *earg;
	extern char *optarg;
	extern int optind, optopt;
    
	while ((c = getopt(argc, argv, "d:e:l:s")) != -1) {
        
		switch(c) {
			
		case 's':
			statflag=1;
			break;
		case 'l':
			maxMatchNumber = atoi(optarg);
			
			break;
		case 'd':
			darg = optarg;
			dflag=1;
			minMatchLength = atoi(darg);
			break;
		case 'e':
			earg = optarg;
			extendSeed=atoi(earg);
			printf("Extension length: %d\n",extendSeed);
			break;
		case ':':       /* -f or -o without operand */
			fprintf(stderr,
				   "Option -%c requires an operand\n", optopt);
			errorflag++;
			break;
		case '?':
			printf("");
			fprintf(stderr,
				    "Unrecognized option: -%c\n", optopt);
			errorflag++;
		}
	}
    
	if (errorflag) {
		printUsageAndExit();
	}
    
	if (dflag==0) {
		printUsageAndExit();
	}
	
	index = optind;
	if (index < argc) {
		//fileA = argv[index];
		fileA = (char *) calloc(1024,sizeof(char));
		strcpy(fileA, argv[index]);
	} else {
		fprintf (stderr,"please give target file\n");
		exit(2);
	}
	index++;
	if (index < argc) {
		//fileB = argv[index];
		fileB = (char *) calloc(1024,sizeof(char));
		strcpy(fileB, argv[index]);
	} else {
		fprintf (stderr,"please give querry file\n");
		exit(2);
	}
	index++;
	if (index < argc) {
		fprintf(stderr,"too many arguments\n");
		exit(2);
	}
	
//exit(0);
	
//-------------------------------------
	
	toNum = (int *) malloc(256*sizeof(int));
	
	for (i=0; i<256; i++) {
		toNum[i] = 5; // everything else
	}

	toNum['a']=0;
	toNum['g']=1;
	toNum['c']=2;
	toNum['u']=3;
	toNum['#']=5;
	



	//e=8; // minimal matchlength to be reported !
	printf("Minimal match length: %d\n",minMatchLength);
	
	
	seqSetA = parseFile(fileA);
	seqSetB = parseFile(fileB);
		
	//exit(0);
	//printf("%s\n",seq1);
	//printf("A:%s\n",seqSetA->sequence);
	//printf("B:%s\n\n",seqSetB->sequence);
	
	printf("\n");

	

	
	int * suffixesA = getSuffixNumbers(seqSetA);
	int * suffixesB = getSuffixNumbers(seqSetB);

//printf("zahlen: %d\n",suffixesA[1]);
//printf("zahlen: %d\n",suffixesA[2]);

	//int * resultList;
	struct matchList *matchList = (struct matchList *) malloc(sizeof(struct matchList ));
	matchList->firstMatch=NULL;
	matchList->lastMatch=NULL;

	// main-algorithm:
	doRecursion(matchList,0, 1, suffixesA[0]-1,1,suffixesB[0]-1,suffixesA,suffixesB,seqSetA->sequence,seqSetB->sequence);
	

	
	printf("\n");
	
	printResults(matchList,seqSetA,seqSetB);
	
	
	
	free(suffixesA);
	free(suffixesB);
		
	return 0;

}

printUsageAndExit(){
	fprintf(stderr,"\nUsage: guugle [OPTION]... TARGET QUERY\n\n");
	fprintf(stderr,"    TARGET and QUERY are Fasta files containing RNA sequences\n");
	fprintf(stderr,"    (Nucleotided T will be converted to U internally and will shown as U\n");
	fprintf(stderr,"     in the output.)\n\n");
	fprintf(stderr,"    -d x, obligatory, output only matches with length of at least x\n");
	fprintf(stderr,"    -e y, switch output mode, show target seeds extended by y bases in \n");
	fprintf(stderr,"           either direction\n");
	fprintf(stderr,"    -l z, limit output to first z matches\n");
	fprintf(stderr,"    -s, show match length distribution\n\n");
	//fprintf(stderr, "usage: . . . ");
	
	exit(2);
}


printResults( struct matchList *matchList, struct sequenceContainer *seqSetA, struct sequenceContainer *seqSetB){

	struct match *match;

	if (statflag) {
		match = matchList->firstMatch;
		count = (int *) calloc(1000,sizeof(int));
		
		while (match != NULL) {

			//count[depth]++; // TODO > 1000 is possible
			if (match->distance > statmax) {
				count[0]++;
			} else {
				count[match->distance]++;
			}
			
			match = match->nextMatch;
		}


		// Output of number of matches
		printf("RNA perfect matches computed by GUUGle:\n");
		

		int i;
		for (i=1; i<1000; i++) {
			if (count[i]!=0){
				printf("Length %d: %d\n",i,count[i]);
			}
		}
		if (count[0]!=0) {
			printf("Length longer than %d: %d\n",statmax,count[i]);
		}
		printf("\n");

	}
	
	match = matchList->firstMatch;
	while (match != NULL) {
		
		int depth = match->distance;
		int i = match->target;
		int j = match->query;
		
		int numberA = getSeqAndDescrStart(seqSetA, i);
		int numberB = getSeqAndDescrStart(seqSetB, j);
				
		char * descrA = getDescription(seqSetA, numberA);
		char * descrB = getDescription(seqSetB, numberB);
				
				
		if (extendSeed  == -1 ) {// MODE match
			printf("MatchLength: %d ",depth);
			printf("\"%s\" at %d vs. \"%s\" at %d \n",
					descrA,
					i-seqSetA->sequPos[numberA],
					descrB,
					j-depth+1-(seqSetB->sequPos[numberB])
			);
			printHybridization(depth, i,i+depth,
					j,j-depth, seqSetA->sequence, seqSetB->sequence);
			printf("\n");
		} else {//MODE target
			printf(">%s_at_%d_with_%s_at_%d\n",
					descrA,
					i-seqSetA->sequPos[numberA],
					descrB,
					j-depth+1-(seqSetB->sequPos[numberB])
			);
		
			printTargetRegion(depth, i,i+depth, seqSetA->sequence);
		}
		free(descrA);
		free(descrB);
		
		
		//printf("match: %d %d %d\n",match->distance,match->target,match->query);
		match = match->nextMatch;
	}
	
	if (maxMatchNumber > -1) {
		if (matchNumber >= maxMatchNumber) {
			printf("Maximum number (%d) of matches reached. Please choose a higher k or\n",maxMatchNumber);
			printf("download the sourcecode of GUUGle.\n\n");
		}
	}

}


int * getSuffixNumbers(struct sequenceContainer * cont) {

	int length = cont->sequenceLengthTotal;
	int * suffixes = (int *) malloc((length+1)*sizeof(int));
	suffixes[0] = length+1;

	int i;
	int j = 1;
	int k = -1;
	for (i=0; i<cont->numberOfSequences; i++) {

		k = cont->sequPos[i] + 1;

		while ( cont->sequence[k] != '#') {
			suffixes[j] = k;
			//printf("suffixes[%d] = %d;\n",j,k);
			j++;
			k++;
			
		}
	}

	return suffixes;
}

doRecursion(struct matchList *matchList, int depth, int lA, int rA, int lB, int rB, int * suffixesA,
			int * suffixesB, char * seqA, char * seqB){
	
	if (depth >= minMatchLength) {
		printIfMaximal(matchList, depth, lA, rA, lB, rB, suffixesA, suffixesB, seqA, seqB);
	}

	if (maxMatchNumber == -1 || matchNumber < maxMatchNumber) {			
		
		//printf("matchNumber: %d, %d \n",depth, matchNumber);
		
		// printf("---------------------A\n");			
		int * intervalsA = countingSort(depth, suffixesA, seqA, lA, rA);
		// printf("---------------------B\n");			
		int * intervalsB = countingSort(-1*depth, suffixesB, seqB, lB, rB);
					
		//a -> u
		if ( ((intervalsA[1])-intervalsA[0] > 0) && // a
				 ((intervalsB[4])-intervalsB[3] > 0)   ) { //u
				doRecursion(matchList, depth+1,intervalsA[0],intervalsA[1]-1,
							intervalsB[3], intervalsB[4]-1,
							
							suffixesA, suffixesB, seqA, seqB);
		}	
		// c -> g
		if ( ((intervalsA[3])-intervalsA[2] > 0) && // c
				 ((intervalsB[2])-intervalsB[1] > 0)   ) { //g
				doRecursion(matchList, depth+1,intervalsA[2],intervalsA[3]-1,
							intervalsB[1], intervalsB[2]-1,
							
							suffixesA, suffixesB, seqA, seqB);
		}	
		//g -> cu
		if ( ((intervalsA[2])-intervalsA[1] > 0) && // g
				 ((intervalsB[4])-intervalsB[2] > 0)   ) { //cu
				doRecursion(matchList, depth+1,intervalsA[1],intervalsA[2]-1,
							intervalsB[2], intervalsB[4]-1,
					
							suffixesA, suffixesB, seqA, seqB);
		}			
		//u ->ag	
		if ( ((intervalsA[4])-intervalsA[3] > 0) && // u
				 ((intervalsB[2])-intervalsB[0] > 0)   ) { //ag
				doRecursion(matchList, depth+1,intervalsA[3],intervalsA[4]-1,
							intervalsB[0], intervalsB[2]-1,
					 
							suffixesA, suffixesB, seqA, seqB);
		}
		free(intervalsA);
		free(intervalsB);
	}	
}

printIfMaximal(struct matchList * matchList, int depth, int lA, int rA, int lB, int rB, int * suffixesA,
			int * suffixesB, char * seqA, char * seqB){
	int i,j;
	// all pairs of suffixes:
	
	for (i=lA; i<=rA; i++) { // TODO, ist das  sinnvoll ?
		for (j=lB; j<=rB; j++) {

			char a=seqA[suffixesA[i]-1];
			char b=seqB[suffixesB[j]+1];
			char c=seqA[suffixesA[i]+depth];
			char d=seqB[suffixesB[j]-depth];
			
			

			/*  //debugging:
			printf("Left : %c %c\n",a,b);
			if ( (a == '#') || ( b== '#') ) {
				printf("raute\n");
			} else {
				printf("not-raute\n");
			}
			if (isComplement(a,b)==1) {
				printf("compl\n");
			} else {
				printf("not-compl\n");
			}

			
			printf("Right : %c %c\n",c,d);
			if ((c == '#') || (d == '#')) {
				printf("raute\n");
			} else {
				printf("not-raute\n");
			}
			if (isComplement(c,d)==1) {
				printf("compl\n");
			} else {
				printf("not-compl\n");
			}
			*/
			
			
			
			if (maxMatchNumber == -1 || matchNumber < maxMatchNumber) {
				//check for leftmaximality, both # or not complementary bases  a||(b&&c)
				//check for rightmaximality, both # or not complementary bases
				if (( ! isComplement(a,b)==1 )&&( ! isComplement(c,d)==1 )) {
	
					
					
					struct match *newMatch = (struct match *) malloc(sizeof(struct match));
					newMatch->nextMatch=NULL;	
					newMatch->distance=depth;
					newMatch->target=suffixesA[i];
					newMatch->query=suffixesB[j];
	
					if (matchList->firstMatch == NULL) {
						matchList->firstMatch=newMatch;
					} else {
						matchList->lastMatch->nextMatch = newMatch;	
					}
					
					matchList->lastMatch = newMatch;
					
					matchNumber++;
					//printf("HUHU: %d\n",matchNumber);
					//if (maxMatchNumber > -1) {
						
						//if (matchNumber >= maxMatchNumber) {
						//	printf("Maximum number of matches reached. Please choose a higher k or\n");
						//	printf("download the sourcecode of GUUGle.\n\n");
						//	exit(0);
						//}
					//}
					
					
				}
			}	
		}
	}
}

printTargetRegion(int depth, int a, int b,
			char * seqA){
	if (a<=b) { // TODO other cases ?????if kann evtl weg
				
		char *text;
		int start,stop;
		//printf("\nfound:\n");
		start = a;
		while (seqA[start-1]!= '#' && start > a-extendSeed) {
			start--;
		}
		stop = b;
		
		while (seqA[stop]!= '#' && stop < b+extendSeed) {
			stop++;
		}
		
		text = (char *) malloc((stop-start+1)*sizeof(char));
		text = memcpy(text,&seqA[start], stop-start+1);
		text[stop-start]='\0';
		
		printf("%s\n",text);
		free(text);
		
		
		
	} else {
		printf("printHybridization: autsch!/n");
		exit(1);
	}

				
}


printHybridization(int depth, int a, int b, int c, int d, char * seqA, char * seqB){
	if ((a<=b) && (c>=d)) { // TODO other cases ?????if kann evtl weg
				
		char *text;
		//printf("\nfound:\n");
		text = (char *) malloc((b-a+1)*sizeof(char));
		text = memcpy(text,&seqA[a], b-a+1);
		text[b-a]='\0';
		
		printf("5%s3\n",text);
		free(text);
		
		
		text = (char *) malloc((c-d+1)*sizeof(char));
		int i;
		for (i = c-d; i>=0; i--) {
			text[i]=seqB[c-i];
		}
		text[c-d]='\0';
		printf("3%s5\n",text);
		free(text);
		
	} else {
		printf("printHybridization: autsch!/n");
		exit(1);
	}

				
}


// sorts the suffixes of an interval of suffixArray
int * countingSort(int depth, int * suffixes, char * seq, int l, int r){
	int count[6] = {0,0,0,0,0,0}; //a,c,g,u,#,N

	int i = 0;

	//printf("eingang:\n");
	for (i=l; i<=r; i++){
		count[toNum[seq[suffixes[i]+depth]]]++;
	}
	
	
	
	for (i=1; i<6; i++) {
		count[i]+=count[i-1];
	}
	
	
	
	int * tmp = (int *) malloc((r-l+1)*sizeof(int));
	
	for (i=r; i>=l; i--){
		int x = toNum[seq[suffixes[i]+depth]];
		tmp[count[x]-1] = suffixes[i];
		count[x]--;
	}	

	//change array of suffixes
	for (i=0; i<r-l+1; i++) {
		suffixes[i+l] = tmp[i];
	}
	
	free(tmp);
	
	// get intervalls
	int * intervals = (int *) malloc(6*sizeof(int));
	
	for (i=0; i<6; i++) {
		intervals[i] = -1;
	}
	

	
	for (i=l; i<=r; i++) {
		
		int x = toNum[seq[suffixes[i]+depth]];
		if (intervals[x] == -1) {
			intervals[x] = i;
		}
	}


	
	int upperBorder=r+1;
	for (i=5; i>=0; i--) {
		if (intervals[i] == -1) {
			intervals[i] = upperBorder; //if the base doesn't appear
		} else {
			upperBorder = intervals[i];
		}
	}
	
	
	return intervals;
}

// for debugging
printSuffix(int s, char * seq){
	
	int length=0;
	while (seq[s+length] != '#') {
		length++;
	}
	 
	char * tmp = (char *) malloc((length+1)*sizeof(char));
	tmp = memcpy(tmp,&seq[s],length);
	tmp[length] = '\0';
	printf("Suffix(%d)(%d):%s\n", s, length, tmp);
}






char * getDescription(struct sequenceContainer *cont, int descr){
	
	int descrEnd, descrBegin;
	descrBegin = cont->descPos[descr];
	
	
	descrEnd = cont->sequPos[descr]-1;
	
	
	int length = descrEnd - descrBegin + 1;
	//maxlength for description:
	if (length > 100) {
		length = 100;
	}
	char *text;
	
	//printf("Q-descr: %d\n",descr);
	//printf("Q-descrBegin: %d\n",descrBegin);
	//printf("Q-descrEnd: %d\n",descrEnd);
	//printf("Q-length: %d\n",length);
	
	text = (char *) malloc((length+1)*(sizeof(char))); // Fehlerquelle ?
	text = memcpy(text,&cont->sequence[descrBegin], length);
	text[length]='\0';
	return text; 
}

// for a given position in the sequence,it says to which i'th sequence it belongs
int getSeqAndDescrStart(struct sequenceContainer *cont, int pos) {
	int i;

	int foundAt=-1;
	
	// TODO use binary search
	for (i=0; (foundAt == -1) && (i < cont->numberOfSequences-1); i++){
			//printf("i: %d\n",i);
			//printf("cont->sequPos[i]: %d\n",cont->sequPos[i]);
			//printf("cont->sequPos[i+1]: %d\n",cont->sequPos[i+1]);

		if ((pos>cont->sequPos[i])&&(pos<=cont->sequPos[i+1])) {
			foundAt=i;
		}
	}

	if  (pos > cont->sequPos[cont->numberOfSequences-1] &&
			pos <= cont->sequenceLengthTotal+cont->descriptionLengthTotal+2*cont->numberOfSequences +1) {
				foundAt = cont->numberOfSequences-1;
	}
	
	if (foundAt==-1) {
		printf("max: %d \n",cont->sequenceLengthTotal+cont->descriptionLengthTotal+2*cont->numberOfSequences +1);
		printf("seq: %s\n",cont->sequence);
		printf("Error: Sequence for sequenceposition '%d' not found!\n",pos);
		exit(1); //TODO other number ?
	}
	return foundAt;
}


int isComplement(char a, char b){
	//if (a == NULL || b == NULL) {
	//	printf("isComplement: NULL!\n");
	//	exit(1);
	//}
	return compl[toNum[a]][toNum[b]];
}

//appends second argument to list (first argument)
appendList(struct list *liste, struct listElement *newElem){
	
	if (liste->begin == NULL || liste->end == NULL) { 
		liste->begin=newElem;
	} else {
		liste->end->next=newElem;
	}
	liste->end = newElem;
}

int nextDescriptionStart(char *seq, int begin){
	int i= begin;
	int newline = 0;
	if (seq[begin-1] == '\n') {
		newline = 1;
	}
	
	if (begin == 1){
		newline = 1;
	}
	
	while (seq[i]!='\0') {
		if ((seq[i]=='>')&&(newline == 1)) {
			return i;
		} 
		newline=0;
		if (seq[i]=='\n') {
			newline=1;
		}
		i++;
		
	}
	return -1; // not found
}

int nextLineBreak(char *seq, int begin){
	int i= begin;
	
	while (seq[i]!='\0') {
		if (seq[i]=='\n') {
			return i;
		}
		i++;
	}
	return i; // not found
}

int isThereData(char *seq, int begin, int end){
	
	int i = begin;
	
	if (end == -1) {
		while (seq[i] != '\0'){
			if (isalpha(seq[i]) > 0) {
				return 1;
			}
			i++;
		}
		
		
	} else {
	
		while (i <= end){
			if (isalpha(seq[i]) > 0) {
				return 1;
			}
			i++;
		}
	}	
	return 0;
}

struct sequenceContainer * parseFile(char *file){
	int i,j;
	FILE *file_ptr;
	file_ptr = fopen(file,"r");
	int file_size;
	if (file_ptr==NULL) {
		printf("Error opening file: %s\n",file);
		exit(0);
	}
	else {
		fseek(file_ptr,0,SEEK_END);
		
		file_size = (int) ftell(file_ptr); //TODO cast ist doof
		//printf("filesize: %d\n",file_size);
	}
	printf("Opening file: %s\n",file);
	
	
	//file in memory
	char *wholeSequence;
	
	
	wholeSequence = (char *) malloc( (file_size + 3) * sizeof(char)); //+3, maybe for 2 #'s and 1 \0.
	
	fseek(file_ptr,0,SEEK_SET);
	int read = fread(wholeSequence+1,sizeof(char),file_size,file_ptr);
	//printf("read: %d\n",read);
	
	if (read != file_size) {
		printf("Not enough memory ? have read: %d, but filesize: %d\n",read, file_size);
		exit(0);
	}
	wholeSequence[file_size + 1]='\0';
	wholeSequence[file_size + 2]='\0'; //TODO stimmt das ?

	
	int sequenceLengthTotal=0;
	int descriptionLengthTotal=0;
	int numberOfSequences=0;
	
	int newline=1;
	int sequenceDescription = 0;
	
	int lastDescription=-1;
	
	// they will contain the startposition(relative to the file) for each description/sequence
	struct list *descrList,*seqList;
	NEW_LIST(descrList);
	NEW_LIST(seqList);

	
	int writePointer =1;
	int readPointer =1;
	wholeSequence[0]='#';
	//printf("start: %d,%d\n",writePointer,readPointer);
	//none=0, description=1, data=2
	i=0;

	int descriptionStart;

	int currentPosition=1;
	
	while ((descriptionStart = nextDescriptionStart(wholeSequence, currentPosition)) > -1 ) {
		currentPosition = descriptionStart;
		int lineBreak = nextLineBreak(wholeSequence, currentPosition);
		int secondDescriptionStart = nextDescriptionStart(wholeSequence, lineBreak);
		
		//printf ("descriptionStart: %d\n",descriptionStart);
		//printf ("lineBreak: %d\n",lineBreak);
		//printf ("secondDescriptionStart: %d\n\n",secondDescriptionStart);
	
		if ((lineBreak < secondDescriptionStart) || (secondDescriptionStart== -1)) {
			
			if (isThereData(wholeSequence, lineBreak, secondDescriptionStart) == 1) {
				//description: descriptionStart - lineBreak
				//data: lineBreak - secondDescriptionStart
				
				
				
				struct listElement *newElemDescr,*newElemSeq;
				
				
				numberOfSequences++;
				
				
				//printf ("data!\n");
				//printf("Lese: ");
				
				NEW_LIST_ELEMENT(newElemDescr);
				newElemDescr->pos = writePointer;
				//printf("newElemDescr->pos = writePointer: %d\n",writePointer);
				appendList(descrList, newElemDescr);				
				
				for (i=descriptionStart+1; i<lineBreak; i++){
					//printf("%c",wholeSequence[i]);
					wholeSequence[writePointer++] = wholeSequence[i];
					descriptionLengthTotal++;
				}
				//printf("\n");
				
				wholeSequence[writePointer++] = '#';
				
				//printf("Data: ");
				
				NEW_LIST_ELEMENT(newElemSeq);	
				newElemSeq->pos = writePointer-1; 
				appendList(seqList, newElemSeq);				
				
				
				
				if (secondDescriptionStart == -1) {
					while( wholeSequence[i] != '\0') {
						if (isalpha(wholeSequence[i]) ) {
							//printf("%c",wholeSequence[i]);
							wholeSequence[writePointer++] = wholeSequence[i];
							sequenceLengthTotal++;
						}
						i++;
					}
				} else {
					for( i=lineBreak; i<secondDescriptionStart; i++) {
						if (isalpha(wholeSequence[i]) ) {
							//printf("%c",wholeSequence[i]);
							wholeSequence[writePointer++] = wholeSequence[i];
							sequenceLengthTotal++;
						}
						
					}
				}
				//printf("\n");
				wholeSequence[writePointer++] = '#';
				
				
			} else {
				printf ("\nWarning: found empty sequence!\n");
			}
			
			
		}
		
		//if (secondDescriptionStart > -1) {
		//	currentPosition = secondDescriptionStart -1;
		//} else {
			
			currentPosition = lineBreak;
		//}
		
		
		
		
	}

	//printf("writePointer: %d\n",writePointer);
	
	wholeSequence[writePointer-1] = '#';
	wholeSequence[writePointer] = '\0'; //TODO pruefen ?

	// reduces memory usage:
	wholeSequence = (char *) realloc(wholeSequence,(size_t) writePointer+1);




	// polishing raw sequences (deleting of invalid characters):
	struct listElement *thisDescr,*thisSeq,*tmp;
	
	
	if (descrList->begin != NULL && seqList->begin != NULL) {
		thisDescr = descrList->begin;
		thisSeq = seqList->begin;
	}


	char mask[256];
	mask[256]='\0';
	for (i=0; i<256; i++) {
		mask[i] = 'n'; //change all unknown signs to 'N'
	}
	mask['a']='a';
	mask['c']='c';
	mask['g']='g';
	mask['t']='u';
	
	mask['u']='u';
	mask['U']='u';
	mask['A']='a';
	mask['C']='c';
	mask['G']='g';
	mask['T']='u';
	
	mask['#']='#';
	
	
	
	i=0;
	int mode=2;
	while (wholeSequence[i] != '\0') {
		if (mode == 2) { // for data
			if (wholeSequence[i] == '#') {
				mode = 1;
			} else {
				wholeSequence[i]=mask[wholeSequence[i]];
			}
		} else {
			if (wholeSequence[i] == '#') {
				mode = 2;
				
			}
			
		}
		
		i++;
	}
	
	
	
	//make a int[] out of the list:
	int *descPos = (int*) malloc (sizeof(int)*numberOfSequences);
	int *sequPos = (int*) malloc (sizeof(int)*numberOfSequences);

	if (descrList->begin != NULL && seqList->begin != NULL) {
		thisDescr = descrList->begin;
		thisSeq = seqList->begin;
	}

	i=0;
	while (thisDescr != NULL && thisSeq != NULL ) {
		descPos[i] = thisDescr->pos;
		//printf("descPos[%d]:%d\n",i,descPos[i]);
		sequPos[i] = thisSeq->pos;
		//printf("sequPos[%d]:%d\n",i,sequPos[i]);
		tmp=thisDescr;
		thisDescr = thisDescr->next;
		free(tmp);
		tmp=thisSeq;
		thisSeq = thisSeq->next;
		free(tmp);
		i++;
	}
	
	free(thisDescr);
	free(thisSeq);
	free(descrList);
	free(seqList);
	
	// creating result structure
	struct sequenceContainer *result;
	result = (struct  sequenceContainer*) malloc(sizeof(struct sequenceContainer)); 

	result->sequence=wholeSequence;

	result->descriptionLengthTotal=descriptionLengthTotal;
	result->sequenceLengthTotal=sequenceLengthTotal;
	result->numberOfSequences=numberOfSequences;
	result->descPos = descPos;
	result->sequPos = sequPos;

	
	return result;
}

