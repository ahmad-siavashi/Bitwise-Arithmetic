// Praise be to Allah
// Author: Ahmad Siavashi (ahmad.siavashi@gmail.com)
// Date: Summer 2016
// Description: Performing Bitwise Addition & Multiplication
// Language: C++

#pragma once

unsigned long long int add(unsigned long long int op1, unsigned long long int op2){
	// a, b, c
	int sum[2][2][2] = {
		// a = 0
			{
				// b = 0
				{
					// c = 0
					0,
					// c = 1
					1
				},
				// b = 1
				{
					// c = 0
					1,
					// c = 1
					0
				}
			},
			// a = 1
			{
				// b = 0
				{
					// c = 0
					1,
					// c = 1
					0
				},
				// b = 1
				{
					// c = 0
					0,
					// c = 1
					1
				}
			}
	};
	// a, b, c
	const int cout[2][2][2] = {
		// a = 0
			{
				// b = 0
				{
					// c = 0
					0,
					// c = 1
					0
				},
				// b = 1
				{
					// c = 0
					0,
					// c = 1
					1
				}
			},
			// a = 1
			{
				// b = 0
				{
					// c = 0
					0,
					// c = 1
					1
				},
				// b = 1
				{
					// c = 0
					1,
					// c = 1
					1
				}
			}
	};
	const int step = sizeof(long long) * 8;
	unsigned long long result = 0;
	int cin = 0, co = 0;
	int i = 0;
	while (i < step){
		int a = op1 & 1;
		op1 >>= 1;
		int b = op2 & 1;
		op2 >>= 1;
		// Sum
		int s = sum[a][b][cin];
		// Cout
		co = cout[a][b][cin];
		unsigned long long mask = s;
		mask <<= i;
		result |= mask;
		cin = co;
		i++;      
	}
	return result;
}

long long int multiply(long long int multiplicand, long long int multiplier){
	union tagProduct {
		long long int signedPart;
		unsigned long long int unsignedPart[2];
	}product;

	product.signedPart = multiplier;
	product.unsignedPart[1] = 0;
	unsigned long long int multiplicandComplement = (~multiplicand) + 1;
	int step = sizeof(unsigned long long int) * 8;
	int previousBit = 0;
	while (step-- > 0){
		int currentBit = product.unsignedPart[0] & 1;
		if (currentBit > previousBit){
		  // Subtraction
			product.unsignedPart[1] = add(product.unsignedPart[1], multiplicandComplement);
		}
		else if (currentBit < previousBit){
			product.unsignedPart[1] = add(product.unsignedPart[1], multiplicand);
		}
		unsigned long long int bit = (product.unsignedPart[1] & 1) << 63;
		product.unsignedPart[0] >>= 1;
		product.unsignedPart[0] |= bit;
		product.unsignedPart[1] >>= 1;
		previousBit = currentBit;
	}

	return product.signedPart;
}
