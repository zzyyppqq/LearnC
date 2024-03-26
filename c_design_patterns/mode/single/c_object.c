//
// Created by aecg on 2024/3/21.
//

typedef struct _parent {
    int data_parent;
} Parent;


typedef struct _Child {
    struct _parent parent;
    int data_child;
} Child;


struct _Data;

typedef void (*process )(struct _Data* pData);

typedef struct _Data {
    int value;
    process pProcess;
};


typedef struct _Play {
    void* pData;
    void (*start_play)(struct _Play * play);
} Play;