#include <stdio.h>
#include <string.h>

/*
 * E F g G a A b B C d  D  e
 * 0 1 2 3 4 5 6 7 8 9 10 11
 *
 * E A D  G B E
 * 0 5 10 3 7 12
*/

const char *interval[] = {"M1", "m2", "M2", "m3", "M3", "P4", "TT", "P5", "m6", "M6", "m7", "M7"};

int fretStart[] = {0, 7, 3, 10, 5, 0};

int gMaxFrets;
FILE *gConfig;

int majorScale[] = {0, 2, 4, 5, 7, 9, 11};
int minorScale[] = {0, 2, 3, 5, 7, 8, 10};
int majorPenta[] = {0, 2, 4, 7, 9};
int minorPenta[] = {0, 3, 5, 7, 10};
int jpPenta[] = {0, 1, 5, 7, 8};


int scaleHas(int note, int root, int *scale, int size)
{
	int hasNote = 0;
	for (int i = 0; i < size; i++) {
		if ((scale[i] + root) % 12 == note) {
			hasNote = 1;
			break;
		}
	}
	return hasNote;
}

void major(int root, char *scaleName)
{
	int *scale, size;
	if (!strcmp("M", scaleName)) {
		scale = majorScale;
		size = 7;
	} else if (!strcmp("m", scaleName)) {
		scale = minorScale;
		size = 7;
	} else if (!strcmp("MP", scaleName)) {
		scale = majorPenta;
		size = 5;
	} else if (!strcmp("mP", scaleName)) {
		scale = minorPenta;
		size = 5;
	} else if (!strcmp("JP", scaleName)) {
		scale = jpPenta;
		size = 5;
	} else {
		scale = NULL;
		size = -1;
	}
	for (int i = 0; i < gMaxFrets; i++) {
		printf("%4d ", i);
	}
	printf("\n");
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < gMaxFrets; j++) {
			int note = (fretStart[i] + j) % 12;
			if (scaleHas(note, root, scale, size)) {
				printf("-%s- ", interval[(note - root + 12) % 12]);
			} else {
				printf("---- ");
			}
		}
		printf("\n");
	}
}

int fromE(char *note) {
	char *noteNames[] = {"E", "F", "Gb", "G", "Ab", "A", "Bb", "B", "C", "Db", "D", "Eb"};
	for (int i = 0; i < 12; i++) {
		if (!strcmp(note, noteNames[i])) {
			return i;
		}
	}
	return -1;
}

int main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("Usage: %s [SCALE_NAME] [ROOT_NOTE]\n", argv[0]);
		printf("\tMajor Scale: M\n");
		printf("\tMinor Scale: m\n");
		printf("\tMajor Pentatonic Scale: MP\n");
		printf("\tMinor Pentatonic Scale: mP\n");
		printf("\tJapanese Scale: JP\n");
		return -1;
	}
	gConfig = fopen("a.config", "r");
	if (!gConfig) {
		printf("Config file not found\n");
		return -1;
	}
	fscanf(gConfig, "%d", &gMaxFrets);
	major(fromE(argv[2]), argv[1]);
}
