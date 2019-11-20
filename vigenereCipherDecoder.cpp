#include <iostream>
#include <string.h>

// The max length of key we are checking
#define maxKey 20

using namespace std;


// A table containing the frequency of occurence for each letter in the english alphabet
double frequencies[] = {0.0815, 0.0144, 0.0276, 0.0379, 0.1311, 0.0292, 0.0199, 0.0526, 0.0635, 0.0013, 0.0042, 0.0339, 0.0254, 0.0710, 0.0800, 0.0198, 0.0012, 0.0683, 0.0610, 0.1047, 0.0246, 0.0092, 0.0154, 0.0017, 0.0198, 0.0008};

/*
	A function mapping each letter to its matching position on the table
*/
int charToInd(char a){
	return toupper(a) - 65;
}


/*
	A function for estimating the length of the key.
	We iterate for every number between 1 and @maxKey 
	seperating the text into columns and checking the IC
	for each seperation. We suspect that the length of the
	key is the one which gives the highest IC and we 
	return the value.
*/
int keyLentgthEstimate (char *text){
	int **colFreq, msgL, bestNum = 0;
	double *colIC, best = 0.0;

	colIC = new double[maxKey];
	msgL = strlen(text);

	for (int i = 1; i <= maxKey; i++){
		double sumI = 0;

		colFreq = new int*[i];
		for (int j = 0; j < i; j++)
			colFreq[j] = new int[26];

		for (int j = 0; j < i; j++)
			for (int k = 0; k < 26; k++)
				colFreq[j][k] = 0;	
		
		for (int j = 0; j < msgL; j++)
			colFreq[j % i][charToInd(text[j])]++;

		for (int j = 0; j < i; j++){
			int all = 0;
			for (int k = 0; k < 26; k++)
				all += colFreq[j][k];

			for (int k = 0; k < 26; k++)
				sumI += 1.0 * colFreq[j][k] * (colFreq[j][k] - 1) / (all * (all - 1));
		}

		colIC[i - 1] = sumI / i; 				// the average IC for all the columns

		for (int j = 0; j < i; j++)
			delete[] colFreq[j];
		delete[] colFreq;
	}

	for (int i = 0; i < maxKey; i++) 
		if (best < colIC[i]){
			best = colIC[i];
			bestNum = i + 1;
		}

	return bestNum;
}


int main(int argc, char *argv[]){	
	char *message, *key;
	int msgL, susKeyL, **freqCol, *sizeCol;
	double expected[26];
	
	message = argv[1];
	msgL = strlen(message);
	susKeyL = keyLentgthEstimate(message);
	key = new char[susKeyL];

	cout << "The suspected length of the key is " << susKeyL << endl;

	sizeCol = new int[susKeyL];
	for (int i = 0; i < susKeyL; i++)
		sizeCol[i] = msgL / susKeyL;

	for (int i = 0; i < (msgL % susKeyL); i++)
		sizeCol[i]++;

	freqCol = new int*[susKeyL];	
	for (int i = 0; i < susKeyL; i++)
		freqCol[i] = new int[26];

	for (int i = 0; i < susKeyL; i++)
		for (int j = 0; j < 26; j++)
			freqCol[i][j] = 0;


	// counting the appearance of each letter for @susKeyL columns 
	for (int i = 0; i < msgL; i++){
		int colIndex = i % susKeyL, letIndex = charToInd(message[i]);
		freqCol[colIndex][letIndex]++;
	}

	for (int i = 0; i < 26; i++)
		expected[i] = sizeCol[0] * frequencies[i];

	cout << "The key used for encrypting the text was ";

	// Calculating the shift of each row with the chi=squared method and getting the key used
	for (int gramma = 0; gramma < susKeyL; gramma++){
		double minS = 1000000.0;
		int minShift = 0;
		double curS = 0.0;

		for (int i = 0; i < 26; i++){
			curS = 0.0;
			for (int j = 0; j < 26; j++){
				curS += (freqCol[gramma][(i + j) % 26] - expected[j]) * (freqCol[gramma][(i + j)%26] - expected[j]) / expected[j];
			}
			if (minS > curS){
				minS = curS;
				minShift = i;
			}
		}	
		key[gramma] = (char) (minShift + 65);
		cout << (char) (minShift + 65);
	}
	cout << endl;

	// The final decoding of the message. Adding key and ciphertext to get the new letter 
	for (int i = 0; i < msgL; i++){
		int newC;
		newC = (message[i] - key[i % susKeyL] + 26) % 26 + 65;
		cout << (char) newC;
	}
	cout << endl;

	return 0;
}
