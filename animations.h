//{middle, left, right, claw}

//Servo has only a 180 degree which can be used. So all values after 180 can be used to trigger custom functins
//181 == no change
//182 == home position

#define NO_CHANGE 181
#define HOME      182

#define PICKUP_DURATION 5
const uint8_t pickup[3][PICKUP_DURATION][4] = {{{       38,        50, NO_CHANGE,         0},
                                                {NO_CHANGE, NO_CHANGE,       160, NO_CHANGE},
                                                {NO_CHANGE, NO_CHANGE, NO_CHANGE,        90},
                                                {NO_CHANGE, NO_CHANGE,       110, NO_CHANGE},
                                                {       83, NO_CHANGE,        90, NO_CHANGE}},

                                               {{       83,        50, NO_CHANGE,         0},
                                                {NO_CHANGE, NO_CHANGE,       160, NO_CHANGE},
                                                {NO_CHANGE, NO_CHANGE, NO_CHANGE,        90},
                                                {NO_CHANGE, NO_CHANGE,       110, NO_CHANGE},
                                                {       83, NO_CHANGE,        90, NO_CHANGE}},

                                               {{      132,        50, NO_CHANGE,         0},
                                                {NO_CHANGE, NO_CHANGE,       160, NO_CHANGE},
                                                {NO_CHANGE, NO_CHANGE, NO_CHANGE,        90},
                                                {NO_CHANGE, NO_CHANGE,       110, NO_CHANGE},
                                                {       83, NO_CHANGE,        90, NO_CHANGE}}};

#define DROP_DURATION 5
const uint8_t drop[3][DROP_DURATION][4] = {{{       38,        55, NO_CHANGE, NO_CHANGE},
                                            {NO_CHANGE, NO_CHANGE,       150, NO_CHANGE},
                                            {NO_CHANGE, NO_CHANGE, NO_CHANGE,         0},
                                            {NO_CHANGE, NO_CHANGE,       110, NO_CHANGE},
                                            {       83, NO_CHANGE,        90,       110}},

                                           {{       83,        55, NO_CHANGE, NO_CHANGE},
                                            {NO_CHANGE, NO_CHANGE,       150, NO_CHANGE},
                                            {NO_CHANGE, NO_CHANGE, NO_CHANGE,         0},
                                            {NO_CHANGE, NO_CHANGE,       110, NO_CHANGE},
                                            {       83, NO_CHANGE,        90,       110}},

                                           {{      132,        55, NO_CHANGE, NO_CHANGE},
                                            {NO_CHANGE, NO_CHANGE,       150, NO_CHANGE},
                                            {NO_CHANGE, NO_CHANGE, NO_CHANGE,         0},
                                            {NO_CHANGE, NO_CHANGE,       110, NO_CHANGE},
                                            {       83, NO_CHANGE,        90,       110}}};

#define NOTHING_FOUND_DURATION 6
const uint8_t nothingFound[NOTHING_FOUND_DURATION][4] = {{       60, NO_CHANGE, NO_CHANGE, NO_CHANGE},
                                                         {      100, NO_CHANGE, NO_CHANGE, NO_CHANGE},
                                                         {       60, NO_CHANGE, NO_CHANGE, NO_CHANGE},
                                                         {      100, NO_CHANGE, NO_CHANGE, NO_CHANGE},
                                                         {       60, NO_CHANGE, NO_CHANGE, NO_CHANGE},
                                                         {       83, NO_CHANGE, NO_CHANGE, NO_CHANGE}};

