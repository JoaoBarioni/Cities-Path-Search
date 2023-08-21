#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <stack>

using namespace std;

void encontrarTodosCaminhos(const string& cidadeAtual, const string& destino, const unordered_map<string, vector<string>>& grafo, unordered_set<string>& visitados, stack<string>& caminhoAtual) {
    visitados.insert(cidadeAtual);
    caminhoAtual.push(cidadeAtual);

    if (cidadeAtual == destino) {
        stack<string> caminhoTemp = caminhoAtual;
        while (!caminhoTemp.empty()) {
            cout << caminhoTemp.top();
            caminhoTemp.pop();
            if (!caminhoTemp.empty()) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        if (grafo.find(cidadeAtual) != grafo.end()) {
            const vector<string>& vizinhos = grafo.at(cidadeAtual);
            for (const string& vizinho : vizinhos) {
                if (visitados.find(vizinho) == visitados.end()) {
                    encontrarTodosCaminhos(vizinho, destino, grafo, visitados, caminhoAtual);
                }
            }
        }
    }

    visitados.erase(cidadeAtual);
    caminhoAtual.pop();
}

int main() {
    unordered_map<string, vector<string>> grafo = {
        {"Curitiba", {"Paranagua", "Ponta Grossa"}},
        {"Ponta Grossa", {"Jacarezinho", "Guarapuava", "Uniao da Vitoria"}},
        
        {"Guarapuava", {"Francisco Beltrao", "Campo Mourao"}},
        {"Jacarezinho", {"Londrina"}},
        {"Uniao da Vitoria", {}},

        {"Francisco Beltrao", {"Toledo"}},
        {"Campo Mourao", {"Toledo", "Maringa"}},
        {"Londrina", {"Maringa"}},

        {"Maringa", {"Toledo"}}
    };

    string destino = "Curitiba";
    string origem = "Toledo";

    unordered_set<string> visitados;
    stack<string> caminhoAtual;

    cout << "Caminhos encontrados de " << destino << " a " << origem << ":" << endl;
    encontrarTodosCaminhos(destino, origem, grafo, visitados, caminhoAtual);

    return 0;
}
