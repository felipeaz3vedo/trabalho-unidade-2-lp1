#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Classe base de funcionarios
class Funcionario {
protected:
    string nome, id, cargo;
public:
    // Construtor
    Funcionario(string n, string i, string c) : nome(n), id(i), cargo(c) {}

    // Metodo virtual para exibir informacoes dos funcionarios
    virtual void info() {
        cout << nome << " (" << cargo << " - " << id  << ")" << endl;
    }
};

// Classes derivadas (Cargos dos funcionarios)
class Gerente : public Funcionario {
public:
    Gerente(string n, string i) : Funcionario(n, i, "Gerente") {}
};

class Cozinheiro : public Funcionario {
public:
    Cozinheiro(string n, string i) : Funcionario(n, i, "Cozinheiro") {}
};

class Garcom : public Funcionario {
public:
    Garcom(string n, string i) : Funcionario(n, i, "Garcom") {}
};

class Recepcionista : public Funcionario {
public:
    Recepcionista(string n, string i) : Funcionario(n, i, "Recepcionista") {}
};

// Mesas do restaurante
class Mesa { 
public: 
    int numero; 
    bool disponivel;
    Mesa(int n) : numero(n), disponivel(true) {}
    void info() {
        cout << "Mesa " << numero << " - " << (disponivel ? "Livre" : "Ocupada") << endl;
    }
};

// Pratos do cardapio
class Prato {
public:
    string nome;
    double preco;
    Prato(string n, double p) : nome(n), preco(p) {}
    void info() {
        cout << nome << " - R$ " << preco << endl;
    }
};

// Pedido de uma mesa
class Pedido {
public:
    int mesa;
    vector<Prato*> itens;
    Pedido(int m) : mesa(m) {}

    // Calcula o total do pedido
    double total() {
        double t = 0;
        for (auto p : itens) t += p->preco;
        return t;
    }
};

// Reserva de mesa
class Reserva {
public:
    string cliente;
    int mesa;
    string data;
    Reserva(string c, int m, string d) : cliente(c), mesa(m), data(d) {}
    void info() {
        cout << cliente << " - Mesa " << mesa << " - " << data << endl;
    }
};

// Sistema principal do restaurante
class Restaurante {
    vector<Funcionario*> funcs; // Lista dos funcionarios
    vector<Mesa> mesas; // Lista das mesas
    vector<Prato*> cardapio; // Cardapio dos pratos
    vector<Pedido> pedidos; // Pedidos realizados
    vector<Reserva> reservas; // Reservas das mesas

public:
    // Construtor
    Restaurante() {

        // Crias as mesas enumeradas
        for (int i = 1; i <= 8; i++) mesas.push_back(Mesa(i));

        // Cria os pratos iniciais do cardapio
        cardapio.push_back(new Prato("Feijoada", 35.90));
        cardapio.push_back(new Prato("Strogonoff", 28.50));
        cardapio.push_back(new Prato("Salada", 22.00));
        cardapio.push_back(new Prato("Battom", 999.99));

        // Cria os funcionarios iniciais
        funcs.push_back(new Gerente("Tio Patinhas", "G001"));
        funcs.push_back(new Cozinheiro("Creuza", "C001"));
        funcs.push_back(new Garcom("Tiringa", "W001"));
        funcs.push_back(new Garcom("Rossi", "W002"));
        funcs.push_back(new Recepcionista("Dora", "R001"));
    }

    // Destrutor
    ~Restaurante() {
        for (auto f : funcs) delete f;
        for (auto p : cardapio) delete p;
    }

    // Menu principal
    void menuPrincipal() {
        int opcao;
        do {
            cout << endl << "=== RESTAURANTE ===" << endl << endl;
            cout << "[1] Gerente" << endl
                 << "[2] Cozinheiro" << endl
                 << "[3] Garcom" << endl
                 << "[4] Recepcionista" << endl
                 << "[0] Sair" << endl << endl
                 << "Opcao: ";
            cin >> opcao;
            cout << endl;

            // Chama o menu de cada cargo
            if (opcao == 1) menuGerente();
            else if (opcao == 2) menuCozinheiro();
            else if (opcao == 3) menuGarcom();
            else if (opcao == 4) menuRecepcionista();
        } while (opcao != 0);
    }

private:
    // Menu do gerente
    void menuGerente() {
        int opcao;
        do {
            cout << endl << "--- GERENTE ---" << endl;
            cout << "[1] Ver Funcionarios" << endl 
                 << "[2] Add Funcionario" << endl 
                 << "[3] Ver Mesas" << endl 
                 << "[4] Cardapio" << endl 
                 << "[5] Fechar Conta" << endl 
                 << "[0] Voltar" << endl << endl 
                 << "Opcao: ";
            cin >> opcao;
            cout << endl;

            if (opcao == 1) {
                // Lista os funcionarios
                cout << endl << "--- FUNCIONARIOS ---" << endl;
                for (auto f : funcs) f->info();
            }
            
            else if (opcao == 2) adicionarFuncionario();

            else if (opcao == 3) {
                cout << endl << "--- MESAS ---" << endl;
                // mostra o status das mesas
                for (auto m : mesas) m.info();
            }

            else if (opcao == 4) menuCardapio();

            else if (opcao == 5) fecharConta();
        } while (opcao != 0);
    }
    // Adiciona um novo funcionario ao restaurante
    void adicionarFuncionario() {
        string nome, id;
        int tipo;
        
        cout << "Nome: "; 
        cin.ignore(); // resolve o problema do getline apos o cin
        getline(cin, nome); // para receber os nomes com espaços
        cout << "ID: "; 
        cin >> id;
        cout << "Tipo (1-Gerente, 2-Cozinheiro, 3-Garcom, 4-Recepcionista): "; 
        cin >> tipo;
        
        // Cria o funcionario de acordo com o tipo(cargo)
        if (tipo == 1) funcs.push_back(new Gerente(nome, id));
        else if (tipo == 2) funcs.push_back(new Cozinheiro(nome, id));
        else if (tipo == 3) funcs.push_back(new Garcom(nome, id));
        else if (tipo == 4) funcs.push_back(new Recepcionista(nome, id));
        else {
            cout << "Tipo invalido!" << endl;
            return;
        }
        
        cout << "Funcionario adicionado com sucesso!" << endl;
    }
    // Menu do cozinheiro
    void menuCozinheiro() {
        int opcao;
        do {
            cout << endl << "--- COZINHEIRO ---" << endl;
            cout << "[1] Ver Cardapio" << endl 
                 << "[2] Add Prato" << endl 
                 << "[3] Remover Prato" << endl 
                 << "[0] Voltar" << endl << endl 
                 << "Opcao: "; 
            cin >> opcao;
            if (opcao == 1) menuCardapio();

            else if (opcao == 2) {
                // Adiciona um novo prato no cardapio
                string nome; double preco;
                cout << "Nome: "; 
                cin.ignore();
                getline(cin, nome); // para receber nomes com espaços
                cout << "Preco: "; cin >> preco;
                cardapio.push_back(new Prato(nome, preco));
                cout << "Prato adicionado!" << endl;
            }
            else if (opcao == 3) {
                // Remove o prato do cardapio
                menuCardapio();
                int idx; cout << "Numero para remover: "; cin >> idx;
                if (idx > 0 && idx <= cardapio.size()) {
                    delete cardapio[idx-1];
                    cardapio.erase(cardapio.begin() + idx-1);
                    cout << "Removido!" << endl;
                }
            }
        } while (opcao != 0);
    }
    // Menu do garcom
    void menuGarcom() {
        int opcao;
        do {
            cout << endl << "--- GARCOM ---" << endl;
            cout << "[1] Fazer Pedido" << endl 
                 << "[2] Fechar Conta" << endl 
                 << "[0] Voltar" << endl << endl 
                 << "Opcao: ";
            cin >> opcao;
            if (opcao == 1) fazerPedido();
            else if (opcao == 2) fecharConta();
        } while (opcao != 0);
    }
    // Menu do recepcionista
    void menuRecepcionista() {
        int opcao;
        do {
            cout << endl << "--- RECEPCIONISTA ---" << endl;
            cout << "[1] Ver Mesas" << endl 
                 << "[2] Fazer Reserva" << endl 
                 << "[3] Ver Reservas" << endl 
                 << "[4] Cancelar Reserva" << endl 
                 << "[0] Voltar" << endl << endl
                 << "Opcao: ";
            cin >> opcao;
            if (opcao == 1) { 
                cout << endl << "--- MESAS ---" << endl;
                // Mostra os status das mesas
                for (auto m : mesas) m.info(); 
            }
            else if (opcao == 2) fazerReserva();
            else if (opcao == 3) verReservas();
            else if (opcao == 4) cancelarReserva();
        } while (opcao != 0);
    }
    // Faz as reservas das mesas
    void fazerReserva() {
        string nome, data; 
        int mesa;
        
        cout << "Cliente: "; 
        cin.ignore();
        getline(cin, nome);
        cout << "Mesa: ";
        cin >> mesa;
        cin.ignore();
        cout << "Data (DD/MM/AAAA): ";
        getline(cin, data);

        // Verifica se a mesa esta disponivel
        if (mesa > 0 && mesa <= mesas.size()) {
            if (mesas[mesa-1].disponivel) {
                reservas.push_back(Reserva(nome, mesa, data));
                mesas[mesa-1].disponivel = false;
                cout << "Mesa reservada com sucesso!" << endl;
            } else {
                cout << "Mesa já está ocupada ou reservada!" << endl;
            }
        } else {
            cout << "Numero de mesa invalido!" << endl;
        }
    }

    // Lista as reservas feitas
    void verReservas() {
        if (reservas.empty()) {
            cout << "Nenhuma reserva cadastrada!" << endl;
            return;
        }
        cout << endl << "--- RESERVAS ---" << endl;
        for (int i = 0; i < reservas.size(); i++) {
            cout << i+1 << ". "; reservas[i].info();
        }
    }
    // Cancela a reserva
    void cancelarReserva() {
        if (reservas.empty()) {
            cout << "Nenhuma reserva cadastrada!" << endl;
            return;
        }
        
        verReservas();
        int idx;
        cout << endl << "Numero da reserva para cancelar: "; 
        cin >> idx;
        
        if (idx > 0 && idx <= reservas.size()) {
            int mesa = reservas[idx-1].mesa;
            mesas[mesa-1].disponivel = true;
            reservas.erase(reservas.begin() + idx-1);
            cout << "Reserva cancelada! Mesa " << mesa << " liberada." << endl;
        } else {
            cout << "Numero invalido!" << endl;
        }
    }
    // Mostra o cardapio
    void menuCardapio() {
        cout << endl << "--- CARDAPIO ---" << endl << endl;
        for (int i = 0; i < cardapio.size(); i++) {
            cout << i+1 << ". "; cardapio[i]->info();
        }
    }
    // Registra o pedido da mesa
    void fazerPedido() {
        int mesa;
        cout << "Mesa: "; cin >> mesa;
        
        if (mesa <= 0 || mesa > mesas.size()) {
            cout << "Numero de mesa invalido!" << endl;
            return;
        }

        // Verifica se a mesa esta ocupada
        if (!mesas[mesa-1].disponivel) {
            Pedido pedido(mesa);
            
            int opcao;
            do {
                // Mostra o cardapio para o garcom escolher os pratos
                menuCardapio();
                cout << "[0] Finalizar" << endl << endl
                     << "Prato: ";
                cin >> opcao;

                // Adiciona o prato ao pedido
                if (opcao > 0 && opcao <= cardapio.size()) {
                    pedido.itens.push_back(cardapio[opcao-1]);
                    cout << "Adicionado!" << endl;
                }
            } while (opcao != 0);
            
            pedidos.push_back(pedido);
            cout << "Pedido registrado para a mesa " << mesa << "!" << endl;
        } else {
            cout << "Mesa nao esta ocupada! Faca reserva primeiro." << endl;
        }
    }
    // Fecha a conta da mesa e libera
    void fecharConta() {
        int mesa;
        cout << "Mesa para fechar: ";
        cin >> mesa;
        
        if (mesa <= 0 || mesa > mesas.size()) {
            cout << "Numero de mesa invalido!" << endl;
            return;
        }

        bool encontrou = false;
        // Procura o pedido da mesa
        for (int i = 0; i < pedidos.size(); i++) {
            if (pedidos[i].mesa == mesa) {
                cout << endl << "====== CONTA DA MESA " << mesa << " ======" << endl << endl;
                for (auto item : pedidos[i].itens) item->info();
                cout << "---------------------" << endl << "TOTAL: R$ " << pedidos[i].total() << endl << endl;
                
                // Libera a mesa
                mesas[mesa-1].disponivel = true;
                
                // Remove a reserva se existir
                for (int j = 0; j < reservas.size(); j++) {
                    if (reservas[j].mesa == mesa) {
                        reservas.erase(reservas.begin() + j);
                        break;
                    }
                }
                
                // Remove o pedido da lista
                pedidos.erase(pedidos.begin() + i);
                encontrou = true;
                cout << "Conta fechada e mesa liberada!" << endl;
                break;
            }
        }
        
        if (!encontrou) {
            cout << "Mesa sem pedidos ativos!" << endl;
        }
    }
};

// Main
int main() {
    // Cria o sistema do restaurante e inicia o menu principal
    Restaurante r;
    r.menuPrincipal();
    return 0;
}