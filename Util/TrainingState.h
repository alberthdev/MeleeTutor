#ifndef TRAININGSTATE_H
#define TRAININGSTATE_H

typedef struct training_state_s {
    int wavedash_result;
    int wavedash_cum;
    int lcancel_result;
    int lcancel_cum;
    int shorthop_result;
    int shorthop_cum;
} training_state;

extern training_state current_training_state;

#endif