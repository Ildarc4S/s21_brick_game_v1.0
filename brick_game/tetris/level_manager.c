#include "./include/level_manager.h"

int _getScore(Score_t *this) { return this->score; }

void _setScore(Score_t *this, int score) { this->score = score; }

int _getLevel(Level_t *this) { return this->level; }

void _setLevel(Level_t *this, int level) { this->level = level; }

void _convertLineCountToScore(Score_t *this, int line_count) {
  const int convert_score[4] = {100, 300, 700, 1500};
  if (line_count < 4 && line_count > 0) {
    this->score += convert_score[line_count - 1];
  } else if (line_count >= 4) {
    this->score += convert_score[3];
  }
}

void _setScoreLevel(Level_t *this, Score_t *score) {
  this->score.setScore(&this->score, this->score.getScore(&this->score) +
                                         score->getScore(score));
}

void _updateLevel(Level_t *this) {
  this->level = this->score.getScore(&this->score) / this->max_level_score + 1;
  if (this->level > 10) {
    this->level = 10;
  }
}

Score_t constructorScore() {
  return (Score_t){
      .score = 0,
      .getScore = _getScore,
      .setScore = _setScore,
      .convertLineCountToScore = _convertLineCountToScore,
  };
}

Level_t constructorLevel() {
  return (Level_t){.level = 1,
                   .max_level_score = 600,
                   .score = constructorScore(),
                   .getLevel = _getLevel,
                   .setLevel = _setLevel,
                   .setScore = _setScoreLevel,
                   .updateLevel = _updateLevel};
}
