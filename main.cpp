#include <string>
#include <map>

const int LEN = 1e6;
std::string s;
int beg[LEN] = { 0, 0 }, end[LEN] = { 1, 1 }, par[LEN] = { 0, 0 };
std::map<char, int> to[LEN], link[LEN];
int n = 2;

void attach(int kid, int p, char c, int b, int e) {
	beg[kid] = b; end[kid] = e; par[kid] = p;
	to[p][c] = kid;
}

void extend(char c) {
	int p, i = s.size(), old = n - 1;
	for (p = old; !link[p].count(c); p = par[p])
		i -= end[p] - beg[p];
	int v = link[p][c];
	if (to[v].count(s[i])) {
		int j, u = to[v][s[i]];
		for (j = beg[u]; s[j] == s[i]; j += end[p] - beg[p], i += end[p] - beg[p])
			p = to[p][s[i]];
		attach(n, v, s[beg[u]], beg[u], j);
		attach(u, n, s[j], j, end[u]);
		v = link[p][c] = n++;
	}
	link[old][c] = n;
	attach(n++, v, s[i], i, s.size());
}

int main() {
	for (int c = 0; c <= 255; c++)
		to[0][c] = link[0][c] = 1;
	s = "aabababbbbadcasdf#";
	for (int i = s.size() - 1; i >= 0; i--)
		extend(s[i]);
}