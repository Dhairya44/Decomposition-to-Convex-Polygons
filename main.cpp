#include<bits/stdc++.h>
#include<stdio.h>
#include<unistd.h>
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
    int id;
    vector<HalfEdge*> interComponent;
    Face(){
        id = -1;
        interComponent.clear();
    }
    Face(int id, vector<HalfEdge*> interComponent){
        this->id = id;
        this->interComponent = interComponent;
    }
};

class DCEL{
    public:
    vector<Face*> faces;
    vector<Vertex*> vertices;
    vector<HalfEdge*> edges;
    vector<HalfEdge*> diag;

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
        orig->id = 1;
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
            cout<<faces[i]->interComponent.size()<<endl;
            HalfEdge *start = faces[i]->interComponent[0];
            HalfEdge *e = start;
            do {
                cout<<e->org->x<<" "<<e->org->y<<endl;
                e = e->next;
            } while (e != start);
        }
    }

    vector<pair<Vertex*, Vertex*>> findLLE(){
        vector<pair<Vertex*, Vertex*>> lle;
        for(int i = 0;i<faces.size()-1;i++){
            HalfEdge *start = faces[i]->interComponent[0];
            lle.push_back({start->prev->org, start->org});
        }
        return lle;
    }

    void traverse(){
        HalfEdge *start = vertices[0]->incidentEdge;
        HalfEdge *e = start;
        do {
            cout<<e->org->x<<" "<<e->org->y<<endl;
            e = e->next;
        } while (e != start);
    }

    vector<pair<int, Vertex*>> LP(Vertex *v){
        vector<pair<int, Vertex*>> lp;
        for(int i = 0;i<faces.size();i++){
            HalfEdge *start = faces[i]->interComponent[0];
            HalfEdge *e = start;
            do {
                if(e->org == v && e->dest->ind - e->org->ind == 1){
                    break;
                }
                if(e->org==v)
                    lp.push_back({i+1, e->dest});
                e = e->next;
            } while (e != start);
        }
        return lp;
    }

    HalfEdge* findEdge(int face, Vertex *v){
        HalfEdge *start = faces[face-1]->interComponent[0];
        HalfEdge *e = start;
        do {
            if(e->org == v){
                return e;
            }
            e = e->next;
        } while (e != start);
        return start;
    }
    
};

bool angle(Vertex* a, Vertex* b,Vertex* c){
    double x1 = a->x - b->x;
    double y1 = a->y - b->y;
    double x2 = c->x - b->x;
    double y2 = c->y - b->y;
    return (x1*y2 - x2*y1) >= 0;
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

// bool checkIfInside(vector<Vertex*>L, Vertex *v){
//     Vertex *P1 = L[0], *P2 = L[L.size()-1];
//     double slope = (P2->y - P1->y)/(P2->x - P1->x);

//     bool a1 =  v->y > slope*(v->x-P1->x) + P1->y;
//     bool a2 = L[1]->y > slope*(L[1]->x-P1->x) + P1->y;
//     return !(a1 ^ a2);
// }

bool checkIfInside(vector<Vertex*>L, Vertex *v){
    bool flag = true;
    int n = L.size();
    for(int i = 0; i<n; i++){
        Vertex *P1 = L[i], *P2 = L[(i+1+n)%(n)];
        double slope = (P2->y - P1->y)/(P2->x - P1->x);

        bool a1 =  v->y > slope*(v->x-P1->x) + P1->y;
        bool a2 = L[(i+2+n)%n]->y > slope*(L[(i+2+n)%n]->x-P1->x) + P1->y;

        flag &= !(a1 ^ a2);
    }
    return flag;
}

vector<Vertex*> makeConvex(vector<Vertex*> &L, DCEL &dcel){
    Vertex *v1 = L[0], *v2 = L[L.size()-1];
    if(v2->incidentEdge->dest == v1){
        return {};
    }
    HalfEdge *e1 = new HalfEdge(); 
    HalfEdge *e2 = new HalfEdge();
    int id = dcel.faces.back()->id;
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

    f1->id = id;
    f2->id = id+1;
    dcel.edges.push_back(e1);
    dcel.edges.push_back(e2);
    dcel.faces.push_back(f1);
    dcel.faces.push_back(f2);
    dcel.diag.push_back(e1);
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
        // cout<<v1->ind<<endl;
        // for(auto x: L){
        //     cout<<x->ind<<" ";
        // }
        // cout<<endl;
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
        // for(auto x: L)
        //     cout<<x->ind<<" ";
        // cout<<endl;
        if(L[L.size()-1]!=v2){
            P = makeConvex(L, dcel);
            n = n - L.size() + 2;
        }
        m = m+1;
    }
}

void mergeDCEL(DCEL &dcel, vector<int> &lup, vector<HalfEdge*> &redEdges){
    for(int i = 0; i<redEdges.size(); i++){
        HalfEdge *e = redEdges[i];
        HalfEdge *t = redEdges[i]->twin;
        e->prev->next = t->next;
        t->next->prev = e->prev;
        e->next->prev = t->prev;
        t->prev->next = e->next;
        e->org->incidentEdge = t->next;
        Face *f1 = new Face();
        HalfEdge *start = t->next;
        HalfEdge *e1 = start;
            do {
                f1->interComponent.push_back(e1);
                e1->incidentFace = f1;
                e1 = e1->next;
            } while (e1 != start);
        delete(e);
        delete(t);
        dcel.faces.push_back(f1);
    }

    vector<Face*> final;
    map<int, int> m;
    for(int i = 0; i<lup.size(); i++){
        if(lup[i]==i){
            final.push_back(dcel.faces[i]);
        }else if(!m[lup[i]]){
            m[lup[i]]++;
            final.push_back(dcel.faces[lup[i]]);
        }
    }
    // cout<<final.size()<<endl;
    dcel.faces = final;
}

void mergeB(DCEL &dcel){
    vector<HalfEdge*> diag = dcel.diag;
    // for(auto &x: diag)
    //     cout<<x->org->ind<<" "<<x->dest->ind<<" "<<x->incidentFace->id<<" "<<x->twin->incidentFace->id<<endl;
    vector<bool> valid(dcel.faces.size(), true);
    for(int i = 0; i<diag.size(); i++){
        HalfEdge *alpha = diag[i];
        HalfEdge *beta = alpha->twin;
        Face *f1 = alpha->incidentFace, *f2 = beta->incidentFace;
        Vertex *a2 = alpha->org, *b2 = alpha->dest;
        Vertex *a1 = alpha->prev->org, *a3 = beta->next->dest;
        Vertex *b1 = beta->prev->org, *b3 = alpha->next->dest;
        // cout<<a1->ind<<" "<<a2->ind<<" "<<a3->ind<<endl;
        // cout<<b1->ind<<" "<<b2->ind<<" "<<b3->ind<<endl<<endl;
        if(angle(a1, a2, a3) && angle(b1, b2, b3)){
            valid[f1->id-1] = false; valid[f2->id-1] = false;
            valid.push_back(true);
            Face *f3 = new Face();
            f3->id = valid.size();

            alpha->prev->next = beta->next;
            beta->next->prev = alpha->prev;
            alpha->next->prev = beta->prev;
            beta->prev->next = alpha->next;
            alpha->org->incidentEdge = beta->next;
            HalfEdge *start = beta->next;
            HalfEdge *e1 = start;
                do {
                    f3->interComponent.push_back(e1);
                    e1->incidentFace = f3;
                    e1 = e1->next;
                } while (e1 != start);
            delete(alpha);
            delete(beta);
            
            dcel.faces.push_back(f3);
        }
    }
    int cnt = 0;
    for(auto x: valid)
        if(x)
            cnt++;
    //     else
    //         cout<<"invalid ";
    // cout<<endl;
    cout<<cnt<<endl;
    for(int i = 0;i<dcel.faces.size();i++){
        if(!valid[i])
            continue;
        cout<<dcel.faces[i]->interComponent.size()<<endl;
        HalfEdge *start = dcel.faces[i]->interComponent[0];
        HalfEdge *e = start;
        do {
            cout<<e->org->x<<" "<<e->org->y<<endl;
            e = e->next;
        } while (e != start);
    }

}

void merge(DCEL &dcel){
    int n = dcel.vertices.size();
    int NP = dcel.faces.size();
    int m = NP-1;
    vector<bool> ldp(NP, true);
    vector<int> lup(NP);
    for(int i = 0; i<NP; i++){
        lup[i] = i;
    }
    vector<pair<Vertex*, Vertex*>> lle = dcel.findLLE();
    vector<HalfEdge*> redEdges;
    for(int j = 0; j<m; j++){
        Vertex *vs = lle[j].first, *vt = lle[j].second;
        vector<pair<int, Vertex*>> lpvs = dcel.LP(vs), lpvt = dcel.LP(vt);
        // cout<<vs->ind<<" "<<vt->ind<<endl;
        // for(auto x: lpvs)
        //     cout<<"("<<x.first<<", "<<x.second->ind<<") , ";
        // cout<<endl;
        // for(auto x: lpvt)
        //     cout<<"("<<x.first<<", "<<x.second->ind<<") , ";
        // cout<<endl<<endl;
        bool isConvexVs = angle(dcel.vertices[(vs->ind-2 + n)%n], vs, dcel.vertices[(vs->ind)%n]);
        bool isConvexVt = angle(dcel.vertices[(vt->ind-2 + n)%n], vt, dcel.vertices[(vt->ind)%n]);

        if((lpvs.size()>=2 && lpvt.size()>=2) || (lpvs.size()>=2 && isConvexVt) || (lpvt.size()>=2 && isConvexVs) || (isConvexVs && isConvexVt)){
            Vertex *j2 = vt;
            Vertex *i2 = vs;
            HalfEdge *alpha = dcel.findEdge(j+1, j2);
            HalfEdge *beta = dcel.findEdge(j+1, i2);
            Vertex *j3 = alpha->dest;
            Vertex *i1 = beta->prev->org;
            int u;
            for(auto x: lpvt){
                if(x.second==vs){
                    u = x.first;
                    break;
                }
            }
            alpha = dcel.findEdge(u, vt);
            beta = dcel.findEdge(u, vs);
            Vertex *j1 = alpha->prev->org;
            Vertex *i3 = beta->dest;
            // cout<<u<<endl;
            // cout<<j1->ind<<" "<<j2->ind<<" "<<j3->ind<<" "<<i1->ind<<" "<<i2->ind<<" "<<i3->ind<<endl;
            // cout<<endl;
            if(angle(j1, j2, j3) && angle(i1, i2, i3)){
                // cout<<"Merged "<<j+1<<" and "<<u<<endl;
                redEdges.push_back(alpha);
                NP = NP+1;
                ldp[j] = false;
                ldp[u-1] = false;
                ldp.push_back(true);
                for(int h = 0; h<NP-1; h++){
                    if(lup[h] == lup[j] || lup[h] == lup[u-1])
                        lup[h] = NP-1;
                }
                lup[j] = NP-1;
                lup[u-1] = NP-1;
                for(int h = 0; h<NP-1; h++){
                    if(lup[h]==j || lup[h]==u-1)
                        lup[h] = NP-1;
                }
            }
        }
        // cout<<endl;
    }
    // for(int i = 0; i<lup.size(); i++){
    //     cout<<i+1<<" "<<lup[i]+1<<endl;
    // }
    mergeDCEL(dcel, lup, redEdges);
}

int main(){
    DCEL dcel;
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w+", stdout);
    int n;
    cin>>n;
    vector<pair<double, double>> points;
    for(int i = 0; i<n; i++){
        double x, y;
        cin>>x>>y;
        points.push_back({x, y});
    }

    //Reverse if points are in counter clockwise order
    // reverse(points.begin(), points.end());
    dcel.createPolygon(points);
    solve(dcel);
    dcel.traverseFace();
    // merge(dcel);
    mergeB(dcel);
    // dcel.traverseFace();
    return 0;
}