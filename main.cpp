#include <string>
#include <map>

const int MAXLEN = 1e6;
std::string s;
int pos[MAXLEN], len[MAXLEN], par[MAXLEN];
std::map<char, int> to[MAXLEN], link[MAXLEN];
int n = 2;

void attach(int kid, int node, char c, int ln) {
	to[node][c] = kid;
	len[kid] = ln;
	par[kid] = node;
}

void extend(char c) {
	int p, i = s.size(), old = n - 1;
	for (p = old; !link[p].count(c); p = par[p])
		i -= len[p];
	int v = link[p][c];
	if (to[v].count(s[i])) {
		int u = to[v][s[i]];
		for (pos[n] = pos[u] - len[u]; s[pos[n]] == s[i]; pos[n] += len[p], i += len[p])
			p = to[p][s[i]];
		attach(n, v, s[pos[u] - len[u]], len[u] - (pos[u] - pos[n]));
		attach(u, n, s[pos[n]], pos[u] - pos[n]);
		v = link[p][c] = n++;
	}
	link[old][c] = n;
	attach(n, v, s[i], s.size() - i);
	pos[n++] = s.size();
}

int main() {
	len[1] = 1; pos[1] = 0; par[1] = 0;
	for (int c = 0; c <= 255; c++)
		to[0][c] = link[0][c] = 1;
	s = "aabababbbbadcasdf#";
	for (int i = s.size() - 1; i >= 0; i--)
		extend(s[i]);
}