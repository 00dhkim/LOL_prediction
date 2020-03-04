#include "myHeader.h"

int GameDataSize;

int random(int a, int b) {	// [a, b]
	return rand() % (b - a + 1) + a;
}

Gene* init_genes(Gene genes[]) {
	for (int i = 0; i < GENE_LENGTH; i++) {
		genes[i].w[0] = random(-0, MAX_WEIGHT);
		genes[i].w[1] = random(-0, MAX_WEIGHT);
		genes[i].w[2] = random(-0, MAX_WEIGHT);
		genes[i].w[3] = random(-0, MAX_WEIGHT);
		genes[i].w[4] = random(-MAX_WEIGHT, 0);
		genes[i].w[5] = random(-0, MAX_WEIGHT);

		genes[i].correct_count = 0;
	}

	return genes;
}

GameData* readGameData(FILE* f, GameData gamedata[]) {
	fscanf(f, "%d%*c%*s%*c", &GameDataSize);
	for (int i = 0; i < GameDataSize; i++) {
		fscanf(f, "%*s%*c");
		fscanf(f, "%s%*c", gamedata[i].gametype);
		fscanf(f, "%d %d", &gamedata[i].kill.first, &gamedata[i].kill.second);
		fscanf(f, "%d %d", &gamedata[i].gold.first, &gamedata[i].gold.second);
		fscanf(f, "%d %d", &gamedata[i].deal.first, &gamedata[i].deal.second);
		fscanf(f, "%d %d", &gamedata[i].ward.first, &gamedata[i].ward.second);
		fscanf(f, "%d %d", &gamedata[i].damage.first, &gamedata[i].damage.second);
		fscanf(f, "%d %d", &gamedata[i].CS.first, &gamedata[i].CS.second);

		fscanf(f, "%*c%*s%*c");
	}

	return gamedata;
}

Gene* make_correct_count(Gene genes[], GameData gamedata[]) {
	int win_team_score, lose_team_score;

	for (int i = 0; i < GENE_LENGTH; i++) {
		for (int j = 0; j < GameDataSize; j++) {
			win_team_score = \
				genes[i].w[0] * gamedata[j].kill.first + \
				genes[i].w[1] * gamedata[j].gold.first + \
				genes[i].w[2] * gamedata[j].deal.first + \
				genes[i].w[3] * gamedata[j].ward.first + \
				genes[i].w[4] * gamedata[j].damage.first + \
				genes[i].w[4] * gamedata[j].CS.first;
			lose_team_score = \
				genes[i].w[0] * gamedata[j].kill.second + \
				genes[i].w[1] * gamedata[j].gold.second + \
				genes[i].w[2] * gamedata[j].deal.second + \
				genes[i].w[3] * gamedata[j].ward.second + \
				genes[i].w[4] * gamedata[j].damage.second + \
				genes[i].w[4] * gamedata[j].CS.second;

			if (win_team_score > lose_team_score) {
				genes[i].correct_count++;
			}
		}
	}

	return genes;
}

int compareGene(const void* gene1, const void* gene2) {
	// 내림차순으로 정렬

	if (((Gene*)gene1)->correct_count < ((Gene*)gene2)->correct_count) {
		return 1;
	}
	else if (((Gene*)gene1)->correct_count > ((Gene*)gene2)->correct_count) {
		return -1;
	}
	else {
		return 0;
	}
}