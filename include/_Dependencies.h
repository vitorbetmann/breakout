#ifndef DEPENDENCIES_H
#define DEPENDENCIES_H

// External
#include "stdlib.h"
#include <ctype.h>
#include <math.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// Proj specific (i.e. mine, mine, mine!)
#include "LevelMaker.h"
#include "Smile.h"
#include "_Constants.h"
#include "_Util.h"

// States
#include "states/StateEnterHighScore.h"
#include "states/StateGameInit.h"
#include "states/StateGameOver.h"
#include "states/StateHighScore.h"
#include "states/StatePaddleSelect.h"
#include "states/StatePlay.h"
#include "states/StateServe.h"
#include "states/StateStart.h"
#include "states/StateVictory.h"

// Other headers
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"

#endif