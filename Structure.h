

#ifndef STRUCTURE_H_
#define STRUCTURE_H_

#include<cstring>
#include<string>
#include<vector>
#include<map>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cctype>


#define CLOCK_SECOND 1000000.0
#define MAXST 4096
#define N_LABEL_BIT 3
#define USED_BIT 4
#define KEY_MAX 16

#define LABEL_TREE 0
#define LABEL_PATH 1

#define PARA_MAX 1
#define PARA_VTOUR 2
#define PARA_BIDIRECT 4
#define PARA_OURS 1
#define PARA_UPPER 2


#define PARA_SUBVTOUR 8
#define PARA_PATH 16
#define PARA_VPATH 32
#define PARA_SUM 64 #define PARA_TREE 128

#define PARA_OPATH 256
#define PARA_OPATH_MAX 512
#define PARA_OPATH_VPATH 1024
#define PARA_OPATH_BIDIRECT 2048

#define ALG_BASIC 0

#define ALG_MAX (PARA_MAX)
#define ALG_VTOUR (PARA_VTOUR)
#define ALG_MAX_VTOUR (PARA_MAX|PARA_VTOUR)

#define ALG_BIDIRECT (PARA_BIDIRECT)
#define ALG_BIDIRECT_MAX (PARA_BIDIRECT|PARA_MAX)
#define ALG_BIDIRECT_VTOUR (PARA_BIDIRECT|PARA_VTOUR)
#define ALG_BIDIRECT_MAX_VTOUR (PARA_BIDIRECT|PARA_MAX|PARA_VTOUR)

#define ALG_BIDIRECT_TREE_MAX_VTOUR (PARA_BIDIRECT|PARA_TREE|PARA_MAX|PARA_VTOUR)
#define ALG_BIDIRECT_TREE (PARA_BIDIRECT|PARA_TREE)
#define ALG_PATH (PARA_PATH)
#define ALG_PATH_MAX (PARA_PATH|PARA_MAX)
#define ALG_PATH_VTOUR (PARA_PATH|PARA_VTOUR)
#define ALG_PATH_MAX_VTOUR (PARA_MAX|PARA_VTOUR|PARA_PATH)

#define ALG_SUM (PARA_SUM) #define ALG_TREE (PARA_TREE)


#define ALG_SUBVTOUR (PARA_SUBVTOUR)

#define ALG_OPATH_BASIC (PARA_OPATH)
#define ALG_OPATH_MAX (PARA_OPATH|PARA_OPATH_MAX)
#define ALG_OPATH_VPATH (PARA_OPATH|PARA_OPATH_VPATH)
#define ALG_OPATH_MAX_VPATH (PARA_OPATH|PARA_OPATH_MAX|PARA_OPATH_VPATH)
#define ALG_OPATH_BIDIRECT (PARA_OPATH|PARA_OPATH_BIDIRECT)
#define ALG_OPATH_BIDIRECT_VPATH (PARA_OPATH|PARA_OPATH_BIDIRECT|PARA_OPATH_VPATH)
#define ALG_OPATH_BIDIRECT_MAX_VPATH (PARA_OPATH|PARA_OPATH_BIDIRECT|PARA_OPATH_MAX|PARA_OPATH_VPATH)



#define PATH_MUL 1

const int INTINF = 100000000;

const int MAXHEAP = 1100000000;



using namespace std;

vector<int> LBM;int uppercnt;

class Word {
public:
    string st;
    vector<int> v_node;    int pos;    int tlen;public:
    Word( string st );
};

int compare_word(const void *w1, const void *w2);
int compare_word_freq(const void *w1, const void *w2);

class Application {
private:
    static void add_st( char *st, int id, vector<Word*> &v_word, map<string, Word*> &m_word );
    static void save_word_ind_bin( Word** l_word, FILE* f_word_ind, int &now_pos, int s, int t );
    static void union_node_set( vector<int> &v_rst, vector<int> &v_node );
    static void find_word_node( string path, string w, vector<int> &v_node );
    
public:
    static void create_node_index( string path );
    static void create_edge_index( string path );
    static void create_word_index( string path );
    
    static int get_n_node( string path );
    static int get_n_edge( string path );
    static void find_term_node( string path, string term, vector<int> &v_node );
    static string find_node_st( string path, int id );
};


class S {
public:
    static int *n;
    static vector<int> *v;
    
    static int *ns;
    static vector<int> *vs;
    
public:
    static void init();
    static void clear();
};


class PEntry{
public:
    int a, b, set;
    int idx;
    int info;     int cost;
    
public:
    PEntry();
};


class KeyInfo {
public:
    string key;
    int n_node;
    vector<int> v_node;
    
public:
    KeyInfo(string key);
};


class Node {
public:
    int len;
    int *adj;
    int *dis;
    
public:
    Node();
};

class Graph {
private:
    static const int max_node = 30000000;
    
public:
    string path;
    int n, m;
    int *adj;            int *dis;            Node *nodes;        
public:
    Graph();
    ~Graph();
    
public:
    void load( string path );
    void print();
};


class Dijkstra {
private:
    int *dis;
    int *heap;
    int *idx;
    char *flag;     Graph *g;
    int tot;
    
    int n_key;
    int *key_set;
    int *dis_key;
    int max_dis;
    
public:
    Dijkstra();
    Dijkstra(Graph *g, vector<KeyInfo*> &v_key, int *key_set, int key_idx);
    ~Dijkstra();
    
public:
    int size();
    void up( int p );
    void down( int p );
    void enheap( int p, int d );
    void update( int p, int d );
    int deheap();
    int get_max_dis();
    
public:
    int get_dis( int p );
    bool empty();
    int get_dis_key( int key ); };

class BFS {
private:
    int *dis;
    int *queue;
    char *flag;     int head;
    int tail;
    Graph *g;
    
    int n_key;
    int *key_set;
    int *dis_key;
    int max_dis;
    
public:
    BFS();
    BFS(Graph *g, vector<KeyInfo*> &v_key, int *key_set, int key_idx);
    ~BFS();
    
public:
    int size();
    int get_max_dis();
    int dequeue();
    
public:
    int get_dis( int p );
    int get_dis_key( int key );     bool empty();
};

class LBMdist
{
private:
    int *dis;
    int *queue;
    char *flag;     int head;
    int tail;
    Graph *g;
    
    int n_end;    int* v_end;    
    
public:
    LBMdist();
    LBMdist(Graph* g, vector<KeyInfo*> &v_key, int *key_set, int id_one, int* id_all, int length);
    ~LBMdist();
    
public:
    int size();
    int dequeue();
    
public:
    int get_dis( int p );
    int get_max_dis( void );
    bool empty();
};

class DisOracle {
public:
    Graph *g;
    int n_key;
    
    int n;
    int *timestamp;
    int nowtime;
    
    int *visit_now;
    int n_now;
    
    int *src_now;
    int *src_nxt;
    
    int *visit_nxt;
    int n_nxt;
    
    int *seen;
    
    int **dis;
    int **dis_key;
    
    int *key_set;
    
    bool empty;
    int nowd;
    
    bool can_key_dis;
    
public:
    DisOracle(Graph *g, vector<KeyInfo*> &v_key, int *key_set);
    ~DisOracle();
    int get_dis( int i_key, int u );
    int get_dis_key( int i_key, int key );
    void bfs_one_round();
    void disable_key_dis();
};

class PEntryHeap {
public:
    static const int n_block_pentry = 1000000;
public:
    PEntryHeap( DisOracle *d );
    ~PEntryHeap();
    
private:
    vector<PEntry*> v_block;
    vector<int> v_pos;
    
private:
    PEntry* get_entry();
    
private:
    int l;
    PEntry**** tab;     PEntry*** tab_a;     
public:
    int get_dis( int a, int b, int set );     int get_dis( int a, int set );     
private:
    vector<PEntry*> heap;
    int tot;
    
private:
    void up( int p );
    void down( int p );
    
    void enheap( int a, int b, int set, int cost );
    void update( PEntry *e );
    PEntry* deheap();
    bool empty();
    
private:
    void update( int a, int b, int set, int cost );
public:
    void init( DisOracle *d );
};

class Entry {public:
    int set;         int p;             int idx;         int cost;        int val;        int info;         Entry* next;
    
public:
    Entry();
};

class EntryHeap {
private:
    static const int n_block_entry = 1000000;
    static const int init_hash_len = 1111111;
    
private:
    vector<Entry*> v_block;
    vector<int> v_pos;
    
public:
    EntryHeap();
    ~EntryHeap();
    
private:
    Entry* get_entry();
    
private:
    Entry **hash;
    int len_hash;
    int n_hash;
    
private:
    int h( Entry *e );
    int h( int p, int set, int label );
    
public:
    void add( Entry *e );
    Entry *find( int p, int set, int label );
    int len();
    
private:
    vector<Entry*> heap;
    int tot;
    
    void up( int p );
    void down( int p );
    
public:
    void enheap( int p, int set, int label, int val, int cost );
    void update( Entry *e );
    Entry *deheap();
    bool empty();
};

class ResultNode {
public:
    int id;
    vector<ResultNode*> con;
    bool used;
public:
    ResultNode( int id );
};

class ResultTree {
public:
    vector<ResultNode*> v_node;
    map<int, ResultNode*> m_node;
    int n_edge;
    
public:
    ResultTree();
    ~ResultTree();
    ResultNode* get_node( int id );
    void add_edge( int id1, int id2 );
};

class Algorithm {
private:
    Graph *g;
    string query;
    vector<KeyInfo*> v_key;
            DisOracle *d;
    int *key_set;
    int n_key;
    int type;
    int mytype;    ResultTree *rt;
    bool is_tree;
    inline int bitcount(int x) {
        int cnt = 0;
        while(x) {
            x &= (x-1);
            ++cnt;
        }
        return cnt;
    }
    
private:
    EntryHeap *heap;
    PEntryHeap *pheap;
    
private:
    vector<Entry*>* v_entry;
    
private:
    int best;
    int pre_best;
    int pre_min_cost;
    
public:
    int min_cost;
    long tm_start;
    double processing_time;
    double total_memory;
    int heap_len;
    bool succ;
    vector<double> diagram_time;
    vector<double> diagram_qlty;
    vector<double> diagram_memy;
    vector<int> diagram_best;
    vector<int> diagram_minc;
    string fail_reason;
    
    
public:
    static void parse_query( string query, Graph *g, vector<KeyInfo*> &v_key, DisOracle* &d, int *&key_set );
    
private:
    void update( int u, int set, int val );
    void update_path( int u, int set, int val );
    
    int get_lb( int u, int set, int val );
    int get_lb_path( int u, int set, int val );
    
private:
    void create_result_tree( Entry *e );
    void create_result_path_tree( Entry *e );
    void print_result( string st, ResultNode *pre, ResultNode *now );
    
public:
    void run( string path, string query, int type, int mytype, int kwf, int knum );
    
public:
    void print_progress( int cnt, int cnt_tree, int cnt_path );
    void record_progress();
    void print_result( Entry* e );
    void print_diagram();
    double get_memory();
public:    void GetLBM(void);
    int* upper;};

class Exp {
public:
    static const string in_path;
    static const string out_path;
    
    static const int n_knum;
    static const string v_knum[];
    static const string default_knum;
    
    static const int n_dataset;
    static const string v_dataset[];
    
    static const int n_alg;
    static const string v_alg[];
    
    static const int n_kwf;
    static const string v_kwf[];
    static const string default_kwf;
    
    static const double max_apr;
    
public:
    static void draw_diagram(string dataset, string alg, string knum, string kwf);
    static void exp_all();
};

#endif 