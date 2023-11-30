import os  # Importa o módulo 'os' para funcionalidades do sistema operacional

def child_process():  # Função para o processo filho
    print("Hello from child process")  # Imprime uma mensagem do processo filho

def parent_process():  # Função para o processo pai
    print("Hello from parent process")  # Imprime uma mensagem do processo pai
    pid = os.fork()  # Cria um novo processo duplicando o processo atual (pai)

    if pid == 0:  # Verifica se está no processo filho
        child_process()  # Chama a função do processo filho
    else:  # Está no processo pai
        os.wait()  # Espera o processo filho terminar

if __name__ == "__main__":  # Ponto de entrada principal do programa
    parent_process()  # Chama a função do processo pai para iniciar o programa
