#include "word_loader.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "difficulty_types.h"
#include "word.h"

DIFFICULTY IntToDifficulty(int value)
{
	switch (value)
	{
		case 1: return DIFFICULTY::EASY;
		case 2: return DIFFICULTY::MEDIUM;
		case 3: return DIFFICULTY::HARD;
	}
	return DIFFICULTY::EASY;
}

namespace Core {

	void LoadWords(GameState& state, const std::string& filename)
	{
		std::vector<Word> words;
		std::ifstream file(filename);

		if (!file.is_open())
		{
			std::cerr << "ERROR: data file could not be open [" << filename << "]\n";
			return;
		}

		std::string line;

		if (std::getline(file, line))
		{
			std::stringstream ss(line);
			std::string segment;
			if (std::getline(ss, segment, ';'))
				state.LangFrom = segment;
			if (std::getline(ss, segment, ';'))
				state.LangTo = segment;
		}

		while (std::getline(file, line))
		{
			if (line.empty() || line[0] == '#')
				continue;
			
			Word word;
			std::stringstream ss(line);
			std::string segment;
			int part = 0;
			int difficulty_int = 0;

			while (std::getline(ss, segment, ';'))
			{
				switch (part)
				{
					case 0:
						word.From = segment; break;
					case 1:
						word.To = segment; break;
					case 2:
						try { difficulty_int = std::stoi(segment); }
						catch (const std::exception& e)
						{
							std::cerr << "ERROR: conversion from STRING to INT failed\n";
							difficulty_int = 1;
						}
						word.Difficulty = IntToDifficulty(difficulty_int);
						break;
				}
				part++;
			}

			if (part == 3)
				words.push_back(word);
			else
				std::cerr << "ERROR: struct WORD not complete > " << line << "\n";

		}

		state.Words = words;
		return;
	}
}
