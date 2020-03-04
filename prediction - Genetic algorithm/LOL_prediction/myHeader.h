#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

#define GENE_LENGTH 500
#define GENE_LIVE_LENGTH 100
#define MAX_WEIGHT 9999
#define PLAYTIME 20
#define GENE_PRINT_LENGTH 20

extern int GameDataSize;

typedef struct _GameData {
	char gametype[100];			// e.g. 솔랭, 일반, 무작위 총력전 등
	std::pair<int, int> kill;	// 챔피언 처치
	std::pair<int, int> gold;	// 골드 획득량
	std::pair<int, int> deal;	// 챔피언에게 가한 피해량
	std::pair<int, int> ward;	// 와드 설치
	std::pair<int, int> damage;	// 받은 피해량
	std::pair<int, int> CS;		// CS
}GameData;

typedef struct _Gene {
	int w[6];	// weight
	int correct_count;
}Gene;

int random(int a, int b);
Gene* init_genes(Gene genes[]);
GameData* readGameData(FILE* f, GameData gamedata[]);
Gene* make_correct_count(Gene genes[], GameData gamedata[]);
int compareGene(const void* gene1, const void* gene2);
