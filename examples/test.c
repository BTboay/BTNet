#include "btnet.h"

int main(int argc, char **argv)
{
    NetParams *p = load_data_cfg("./cfg/LeNet5.cfg");
    Node *n = p->head;
    while (n){
        LayerParams *l = n->val;
        printf("%s\n", l->type);
        Node *N = l->head;
        while (N){
            Params *pa = N->val;
            printf("%s %s\n", pa->key, pa->val);
            N = N->next;
        }
        n = n->next;
    }
    return 0;
}