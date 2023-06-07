#pragma once

// Values either 0 or 1
#define DEBUG 1
#define DEBUG_COLLISION 1

#if DEBUG
#define DEBUG_SPRITE 1
#define DEBUG_LEVEL 1
#define DEBUG_RAYCAST 1
#define TEST_OBJECT 1
#define DRAW_CENTER_GUIDE 1

#if DEBUG_COLLISION
#define DEBUG_KILLZONE 1
#define DEBUG_TOMBSTONE 1
#define DEBUG_COLLIDER 1
#endif

#endif
