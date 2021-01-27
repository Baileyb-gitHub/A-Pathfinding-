#pragma once
inline void returnError(string errorReason)
{
	cout << "\n ERROR - " << errorReason << endl;
	exit(EXIT_FAILURE);

}