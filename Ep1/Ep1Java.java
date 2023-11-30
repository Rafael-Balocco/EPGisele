// Classe que estende Thread para criar threads que exibirão "Hello world"
class HelloWorldThread extends Thread {
    public void run() {
        // Exibe uma mensagem com o nome da thread atual
      
        System.out.println("Hello World from thread: " + Thread.currentThread().getName());
    
    } //Ao finalizar método Run, finalizamos essa thread
}

// Classe principal que contém o método main
public class Ep1Java {
    public static void main(String[] args) {
        int numThreads = 10; // Número de threads a serem criadas

        // Loop para criar e iniciar várias threads
        for (int i = 0; i < numThreads; i++) {

            // Cria uma nova instância da classe HelloWorldThread
            Thread thread = new HelloWorldThread();
            thread.setName("" + i);

            // Inicia a thread i, invocando o método run()
            thread.start();
        }
    }
}