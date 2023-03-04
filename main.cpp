#include<bits/stdc++.h>
using namespace std;

struct Vertex;
struct HalfEdge;
struct Face;
bool angle(Vertex *a, Vertex *b, Vertex *c);

struct Vertex{
    double x,y;
    int ind;
    HalfEdge* incidentEdge;
    Vertex(double x, double y, int ind){
        this->x = x;
        this->y = y;
        this->ind = ind;
        incidentEdge = nullptr;
    }
};

struct HalfEdge{
    Vertex* org;
    Vertex* dest;
    HalfEdge* twin;
    HalfEdge* next;
    HalfEdge* prev;
    Face* incidentFace;
    HalfEdge(){
        org = NULL;
        dest = NULL;
        twin = NULL;
        next = NULL;
        prev = NULL;
        incidentFace = NULL;
    }
    HalfEdge(Vertex* org, Vertex* dest, HalfEdge* twin, HalfEdge* next, HalfEdge* prev, Face* incidentFace){
        this->org = org;
        this->dest = dest;
        this->twin = twin;
        this->next = next;
        this->prev = prev;
        this->incidentFace = incidentFace;
    }
};
struct Face{
    vector<HalfEdge*> interComponent;
    Face(){
        interComponent.clear();
    }
    Face(vector<HalfEdge*> interComponent){
        this->interComponent = interComponent;
    }
};

class DCEL{
    public:
    vector<Face*> faces;
    vector<Vertex*> vertices;
    vector<HalfEdge*> edges;

    void createPolygon(vector<pair<double, double>> &points){
        int n = points.size();
        for(int i = 0; i<n; i++)
            vertices.push_back(new Vertex(points[i].first, points[i].second, i+1));

        for(int i = 0; i<n; i++){
            HalfEdge *e1 = new HalfEdge();
            HalfEdge *e2 = new HalfEdge();
            e1->org = vertices[i];
            e1->dest = vertices[(i+1)%n];
            e2->org = vertices[(i+1)%n];
            e2->dest = vertices[i];
            e1->twin = e2;
            e2->twin = e1;
            vertices[i]->incidentEdge = e1;
            edges.push_back(e1);
            edges.push_back(e2);
        }
        for(int i = 0; i<n; i++){
            vertices[i]->incidentEdge->next = vertices[(i+1)%n]->incidentEdge;
            vertices[i]->incidentEdge->prev = vertices[(i-1 + n)%n]->incidentEdge;
            vertices[i]->incidentEdge->twin->next = vertices[(i-1 + n)%n]->incidentEdge->twin;
            vertices[i]->incidentEdge->twin->prev = vertices[(i+1)%n]->incidentEdge->twin;
        }

        Face *orig = new Face();
        HalfEdge *start = vertices[0]->incidentEdge;
        HalfEdge *e = start;
        do {
            orig->interComponent.push_back(e);
            e->incidentFace = orig;
            e = e->next;
        } while (e != start);
        faces.push_back(orig);
    }

    void traverseFace(){
        cout<<faces.size()<<endl;
        for(int i = 0;i<faces.size();i++){
            cout<<"Face "<<i+1<<endl;
            HalfEdge *start = faces[i]->interComponent[0];
            HalfEdge *e = start;
            do {
                cout<<e->org->ind<<endl;
                e = e->next;
            } while (e != start);
            cout<<endl<<endl;
        }
    }

    void traverse(){
        HalfEdge *start = vertices[0]->incidentEdge;
        HalfEdge *e = start;
        do {
            cout<<e->org->x<<" "<<e->org->y<<endl;
            e = e->next;
        } while (e != start);
    }
    
};

bool angle(Vertex* a, Vertex* b,Vertex* c){
    double x1 = a->x - b->x;
    double y1 = a->y - b->y;
    double x2 = c->x - b->x;
    double y2 = c->y - b->y;
    double cross = x1*y2 - x2*y1;
    return cross >= 0;
}

vector<Vertex*> findLPVS(vector<Vertex*> &L, vector<Vertex*> &P){
    vector<Vertex*> lpvs;
    int n = P.size();
    for(int i = 0; i<n; i++){
        if(!angle(P[(i-1+n)%n], P[i], P[(i+1)%n])){
            if(find(L.begin(), L.end(), P[i]) == L.end())
                lpvs.push_back(P[i]);
        }
    }
    return lpvs;
}

vector<double> findRectangle(vector<Vertex*> &L){
    int n = L.size();
    Vertex *minX, *maxX, *minY, *maxY;
    for(int i = 0; i<L.size(); i++){
        if(i==0){
            minX = L[i];
            maxX = L[i];
            minY = L[i];
            maxY = L[i];
        }
        else{
            if(L[i]->x < minX->x) minX = L[i];
            if(L[i]->x > maxX->x) maxX = L[i];
            if(L[i]->y < minY->y) minY = L[i];
            if(L[i]->y > maxY->y) maxY = L[i];
        }
    }
    return {minX->x, minY->y, maxX->x, maxY->y};
}

bool checkIfInside(vector<Vertex*>L, Vertex *v){
    Vertex *P1 = L[0], *P2 = L[L.size()-1];
    double slope = (P2->y - P1->y)/(P2->x - P1->x);

    bool a1 =  v->y >= slope*(v->x-P1->x) + P1->y;
    bool a2 = L[1]->y > slope*(L[1]->x-P1->x) + P1->y;
    return !(a1 ^ a2);
}

vector<Vertex*> makeConvex(vector<Vertex*> &L, DCEL &dcel){
    Vertex *v1 = L[0], *v2 = L[L.size()-1];
    if(v2->incidentEdge->dest == v1){
        return {};
    }
    HalfEdge *e1 = new HalfEdge(); 
    HalfEdge *e2 = new HalfEdge();
    dcel.faces.pop_back();

    e1->org = v1;
    e1->dest = v2;
    e2->org = v2;
    e2->dest = v1;
    e1->twin = e2;
    e2->twin = e1;
    e1->prev = v1->incidentEdge->prev;
    e1->next = v2->incidentEdge;
    e2->next = v1->incidentEdge;
    e2->prev = v2->incidentEdge->prev;
    v1->incidentEdge->prev->next = e1;
    v1->incidentEdge->prev = e2;
    v2->incidentEdge->prev->next = e2;
    v2->incidentEdge->prev = e1;
    v1->incidentEdge = e1;
    
    Face *f1 = new Face();
    Face *f2 = new Face();

    HalfEdge *start = e2->next;
    HalfEdge *e = start;
        do {
            f1->interComponent.push_back(e);
            e->incidentFace = f1;
            e = e->next;
        } while (e != start);

    vector<Vertex*> P;
    start = e1;
    e = start;
        do {
            f2->interComponent.push_back(e);
            P.push_back(e->org);
            e->incidentFace = f2;
            e = e->next;
        } while (e != start);

    dcel.edges.push_back(e1);
    dcel.edges.push_back(e2);
    dcel.faces.push_back(f1);
    dcel.faces.push_back(f2);
    return P;
}

void solve(DCEL &dcel){
    vector<Vertex*> P = dcel.vertices;
    int n = P.size();
    vector<Vertex*> L;
    L.push_back(dcel.vertices[0]);
    int m = 1;
        
    while(n>3){
        Vertex *v1 = L[L.size()-1], *v2 = v1->incidentEdge->dest;
        L.clear();
        L.push_back(v1); L.push_back(v2);
        int i = 2; Vertex *v3 = v2->incidentEdge->dest;
        while(angle(L[i-2], L[i-1], v3) && angle(L[i-1], v3, L[0]) && angle(v3, L[0], L[1]) && L.size()<n){
            L.push_back(v3);
            i = i+1;
            v3 = v3->incidentEdge->dest;
        }
        
        if(L.size()!=P.size()){
            vector<Vertex*> lpvs = findLPVS(L, P);
            while(lpvs.size()>0){
                vector<double> rec = findRectangle(L);
                double x1 = rec[0], y1 = rec[1], x2 = rec[2], y2 = rec[3];
                bool backwards = false;
                while(!backwards && lpvs.size()>0){
                    Vertex *v;
                    bool vInR;
                    do{
                        v = lpvs[0];
                        vInR = (v->x>=x1 && v->x<=x2 && v->y>=y1 && v->y<=y2);
                        if(!vInR)
                            lpvs.erase(lpvs.begin());
                    }while(!vInR && lpvs.size()>0);

                    if(lpvs.size()>0 && vInR){
                        if(checkIfInside(L, v)){
                            L.pop_back();
                            backwards = true;
                        }else{
                            lpvs.erase(lpvs.begin());
                        }
                    }
                }
            }
        }

        if(L[L.size()-1]!=v2){
            P = makeConvex(L, dcel);
            for(auto &x: P)
                cout<<x->x<<","<<x->y<<" ";
            cout<<endl;
            n = n - L.size() + 2;
        }
        m = m+1;
    }
}

int main(){
    DCEL dcel;
    freopen("input.txt", "r", stdin);
    int n;
    cin>>n;
    vector<pair<double, double>> points;
    for(int i = 0; i<n; i++){
        double x, y;
        cin>>x>>y;
        points.push_back({x, y});
    }
    dcel.createPolygon(points);
    solve(dcel);
    dcel.traverseFace();
    return 0;
}