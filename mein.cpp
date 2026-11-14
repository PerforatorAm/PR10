#include <iostream>
using namespace std;

const int a = 1000;
const int b = 40;

struct c {
    char d[b]; // name (ПІБ)
    char e[b]; // department (відділ)
    double f;  // salary (зарплата)
};

int g = 0; // allocations
int h = 0; // deallocations
long long i = 0; // movedElements

c* j(int k) {
    if (k <= 0) return nullptr;
    c* l = new c[k];
    g++;
    return l;
}

void m(c*& l) {
    if (l != nullptr) {
        delete[] l;
        h++;
        l = nullptr;
    }
}

void n(char o[], const char p[]) {
    int q = 0;
    while (p[q] != '\0' && q < b - 1) {
        o[q] = p[q];
        q++;
    }
    o[q] = '\0';
}

void r(c& s, const c& t) {
    n(s.d, t.d);
    n(s.e, t.e);
    s.f = t.f;
    i++;
}

void u(c& s) {
    cout << "Name (one word): ";
    cin >> s.d;
    cout << "Department (one word): ";
    cin >> s.e;
    cout << "Salary: ";
    cin >> s.f;

    while (!cin || s.f <= 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter a positive salary: ";
        cin >> s.f;
    }
}

void v(const c& s, int w) {
    cout << w << ". " << s.d << " | " << s.e << " | " << s.f << " UAH\n";
}

void x(const c* y, int z) {
    if (z == 0) {
        cout << "Array is empty.\n";
        return;
    }
    cout << "\nEMPLOYEES\n";
    for (int w = 0; w < z; w++) {
        v(y[w], w);
    }
}

int aa(const c* y, int z, const char e[]) {
    for (int w = 0; w < z; w++) {
        int ab = 0;
        while (y[w].e[ab] == e[ab] && e[ab] != '\0') {
            ab++;
        }
        if (y[w].e[ab] == '\0' && e[ab] == '\0') {
            return w;
        }
    }
    return -1;
}

int ac(const c* y, int z, const char e[]) {
    int ad = 0;
    for (int w = 0; w < z; w++) {
        int ab = 0;
        while (y[w].e[ab] == e[ab] && e[ab] != '\0') {
            ab++;
        }
        if (y[w].e[ab] == '\0' && e[ab] == '\0') {
            ad++;
        }
    }
    return ad;
}

void ae(const c* y, int z, const char e[]) {
    int af = 0;
    for (int w = 0; w < z; w++) {
        int ab = 0;
        while (y[w].e[ab] == e[ab] && e[ab] != '\0') {
            ab++;
        }
        if (y[w].e[ab] == '\0' && e[ab] == '\0') {
            v(y[w], w);
            af++;
        }
    }
    if (af == 0) {
        cout << "No employees of this department found.\n";
    }
}

double ag(const c* y, int z) {
    if (z == 0) return 0;
    double ah = 0;
    for (int w = 0; w < z; w++) {
        ah += y[w].f;
    }
    return ah / z; // середня зарплата (додаткова операція для Варіанта 5)
}

int ai(const c* y, int z) {
    if (z == 0) return -1;
    int aj = 0;
    for (int w = 1; w < z; w++) {
        if (y[w].f > y[aj].f) {
            aj = w;
        }
    }
    return aj;
}

bool ak(c*& y, int& z, int& al, const c& am) {
    if (z >= a) return false;
    if (z == al) {
        int an;
        if (al == 0) an = 2;
        else an = al * 2;
        if (an > a) an = a;

        c* ao = j(an);
        if (ao == nullptr) return false;

        for (int w = 0; w < z; w++) {
            r(ao[w], y[w]);
        }
        m(y);
        y = ao;
        al = an;
    }
    r(y[z], am);
    z++;
    return true;
}

bool ap(c*& y, int& z, int& al, int aq) {
    if (aq < 0 || aq >= z) return false;
    if (z == 1) {
        m(y);
        z = 0;
        al = 0;
        return true;
    }
    c* ar = j(z - 1);
    if (ar == nullptr) return false;

    int as = 0;
    for (int w = 0; w < z; w++) {
        if (w != aq) {
            r(ar[as], y[w]);
            as++;
        }
    }
    m(y);
    y = ar;
    z--;
    al = z;
    return true;
}

bool at(c* y, int z, const char d[], const char au[]) {
    for (int w = 0; w < z; w++) {
        int ab = 0;
        while (y[w].d[ab] == d[ab] && d[ab] != '\0') {
            ab++;
        }
        if (y[w].d[ab] == '\0' && d[ab] == '\0') {
            n(y[w].e, au);
            return true;
        }
    }
    return false;
}

bool av(bool aw, const char ax[]) {
    cout << ax << ": " << (aw ? "PASS" : "FAIL") << "\n";
    return aw;
}

void ay() {
    cout << "AUTOMATED TESTS\n";
    int az = 0;
    c* y = nullptr;
    int z = 0;
    int al = 0;

    az += av(z == 0 && y == nullptr, "1. Empty array display state");
    az += av(!ap(y, z, al, 0), "2. Delete from empty array");

    c ba, bb, bc, bd;
    n(ba.d, "Ivanov"); n(ba.e, "IT"); ba.f = 25000;
    n(bb.d, "Petrov"); n(bb.e, "IT"); bb.f = 30000;
    n(bc.d, "Sydorov"); n(bc.e, "HR"); bc.f = 20000;
    n(bd.d, "Koval"); n(bd.e, "IT"); bd.f = 28000;

    ak(y, z, al, ba);
    az += av(aa(y, z, "IT") == 0, "3. Find the only element");
    az += av(ap(y, z, al, 0) && z == 0 && y == nullptr, "4. Delete the only element");

    ak(y, z, al, ba);
    ak(y, z, al, bb);
    ak(y, z, al, bc);

    az += av(ak(y, z, al, bd) && z == 4 && aa(y, z, "IT") == 0 && ac(y, z, "IT") == 3, "5. Add element and preserve data");
    az += av(ap(y, z, al, 0) && y[0].f == 30000, "6. Delete first element");
    az += av(ap(y, z, al, 1) && y[1].f == 28000, "7. Delete middle element");
    az += av(ap(y, z, al, z - 1) && z == 1, "8. Delete last element");

    int be = z;
    az += av(!ap(y, z, al, -1) && z == be, "9. Reject index -1");
    az += av(!ap(y, z, al, z) && z == be, "10. Reject index equal to size");

    while (z < al) {
        ak(y, z, al, ba);
    }
    int bf = al;
    ak(y, z, al, bb);
    az += av(al > bf, "11. Increase full capacity");

    while (z < 100) {
        ak(y, z, al, ba);
    }
    while (z > 0) {
        ap(y, z, al, z - 1);
    }
    az += av(z == 0 && y == nullptr && al == 0, "12. Clear 100 elements");

    ak(y, z, al, bc);
    az += av(z == 1 && aa(y, z, "HR") == 0, "13. Refill after clearing");

    bool bg = true;
    for (int w = 0; w < 50; w++) {
        if (!ak(y, z, al, ba)) bg = false;
        if (!ap(y, z, al, z - 1)) bg = false;
    }
    az += av(bg && z == 1, "14. 50 add-delete cycles");
    az += av(aa(y, z, "Unknown") == -1, "15. Unsuccessful search");

    m(y);
    z = 0;
    al = 0;
    cout << "Passed: " << az << "/15\n\n";
}

int main() {
    cout << "PRACTICAL WORK 10 - DYNAMIC MEMORY\n";
    cout << "Variant 5: Employee (name, department, salary)\n\n";

    cout << "DYNAMIC OBJECT\n";
    c* bh = new c;
    g++;
    u(*bh);
    cout << "Created object: ";
    v(*bh, 0);

    cout << "Change employee department: ";
    cin >> bh->e;
    cout << "Updated department: " << bh->e << "\n";

    delete bh;
    h++;
    bh = nullptr;
    cout << "Single object released; pointer = nullptr\n";

    c* bi = nullptr;
    int z = 0;
    int al = 0;
    int bj;

    cout << "\nEnter number of employees (1-" << a << "): ";
    cin >> bj;

    while (!cin || bj < 1 || bj > a) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Enter a number from 1 to " << a << ": ";
        cin >> bj;
    }

    for (int w = 0; w < bj; w++) {
        c bk;
        cout << "\nEmployee " << w + 1 << "\n";
        u(bk);
        ak(bi, z, al, bk);
    }

    x(bi, z);

    cout << "\nAverage salary: " << ag(bi, z) << " UAH\n";

    int bl = ai(bi, z);
    if (bl != -1) {
        cout << "Highest salary: " << bi[bl].d << " (" << bi[bl].f << " UAH)\n";
    }

    char bm[b];
    cout << "\nEnter department to search: ";
    cin >> bm;
    cout << "Employees of department " << bm << ":\n";
    ae(bi, z, bm);

    char bn[b];
    char bo[b];
    cout << "\nEnter employee name to change department: ";
    cin >> bn;
    cout << "Enter new department: ";
    cin >> bo;

    if (at(bi, z, bn, bo)) {
        cout << "Department changed.\n";
    } else {
        cout << "Employee not found; array unchanged.\n";
    }

    c bp;
    cout << "\nEnter one employee to add to the end.\n";
    u(bp);
    ak(bi, z, al, bp);
    cout << "After adding: size = " << z << ", capacity = " << al << "\n";

    int aq;
    cout << "Enter index to delete (0-based): ";
    cin >> aq;

    if (ap(bi, z, al, aq)) {
        cout << "Element deleted.\n";
    } else {
        cout << "Invalid index; array unchanged.\n";
    }

    x(bi, z);
    cout << "Current size = " << z << ", capacity = " << al << "\n";

    m(bi);
    z = 0;
    al = 0;
    cout << "Array released. Pointer = nullptr\n";

    ay();

    cout << "\nCAPACITY GROWTH COMPARISON\n";
    cout << "Adds | Increase by 1: reallocations/moves | Doubling: reallocations/moves\n";
    const int bq[3] = { 10, 100, 1000 };
    for (int w = 0; w < 3; w++) {
        int n = bq[w];
        long long br = 0;
        for (int bs = 1; bs < n; bs++) br += bs;
        int bt = n;

        int bu = 0;
        long long bv = 0;
        int al2 = 0;
        int z2 = 0;
        while (z2 < n) {
            if (z2 == al2) {
                int an;
                if (al2 == 0) an = 2;
                else al2 * 2; // зсув
                if (al2 == 0) an = 2;
                else an = al2 * 2;
                if (an > n) an = n;
                bv += z2;
                al2 = an;
                bu++;
            }
            z2++;
        }
        cout << n << " | " << bt << "/" << br << " | " << bu << "/" << bv << "\n";
    }

    cout << "\nMEMORY RESOURCE REPORT\n";
    cout << "Allocations: " << g << "\n";
    cout << "Deallocations: " << h << "\n";
    cout << "Active blocks: " << g - h << "\n";
    cout << "Moved elements (including tests): " << i << "\n";

    return 0;
}
