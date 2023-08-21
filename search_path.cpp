#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <stack>

using namespace std;

bool buscarCaminho(const string &origem, const string &destino, const unordered_map<string, vector<string>> &grafo, unordered_map<string, string> &pais)
{
    queue<string> fila;
    unordered_set<string> visitados;

    fila.push(origem);
    visitados.insert(origem);

    while (!fila.empty())
    {
        string cidadeAtual = fila.front();
        fila.pop();

        if (cidadeAtual == destino)
        {
            return true;
        }

        if (grafo.find(cidadeAtual) != grafo.end())
        {
            const vector<string> &vizinhos = grafo.at(cidadeAtual);
            for (const string &vizinho : vizinhos)
            {
                if (visitados.find(vizinho) == visitados.end())
                {
                    fila.push(vizinho);
                    visitados.insert(vizinho);
                    pais[vizinho] = cidadeAtual;
                }
            }
        }
    }

    return false;
}

int main()
{
    unordered_map<string, vector<string>> grafo = {
        {"Curitiba", {"Paranaguá", "Ponta Grossa"}},
        {"Ponta Grossa", {"Jacarezinho", "Guarapuava", "União da Vitória"}},
        {"Guarapuava", {"Francisco Beltrão", "Campo Mourão"}},
        {"União da Vitória", {}},
        {"Jacarezinho", {"Londrina"}},
        {"Francisco Beltrão", {"Toledo"}},
        {"Campo Mourão", {"Toledo", "Maringá"}},
        {"Maringá", {"Londrina", "Toledo"}}};

    string origem = "Curitiba";
    string destino = "Toledo";

    unordered_map<string, string> pais;
    if (buscarCaminho(origem, destino, grafo, pais))
    {
        stack<string> caminho;
        string cidade = destino;
        while (cidade != origem)
        {
            caminho.push(cidade);
            cidade = pais[cidade];
        }
        caminho.push(origem);

        cout << "Caminho encontrado de " << origem << " a " << destino << ":" << endl;
        while (!caminho.empty())
        {
            cout << caminho.top();
            caminho.pop();
            if (!caminho.empty())
            {
                cout << " -> ";
            }
        }
        cout << endl;
    }
    else
    {
        cout << "Não há caminho de " << origem << " a " << destino << "." << endl;
    }

    return 0;
}
