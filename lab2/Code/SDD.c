#include"GrammarTree.h"
#include"syntax.tab.h"

void SDT(){
    SDT_DFS(root);
}

void SDT_DFS(struct GrammarTree *node){
    switch(node->type){
        case ExtDefList: handle_ExtDefList(node);break;
        case DefList:handle_DefList(node);break;
    }
}

void handle_ExtDefList(struct GrammarTree *node){
    
}

void handle_DefList(struct GrammarTree *node){
    
}