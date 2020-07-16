// Exemplo de definicao de tratador de sinal UNIX
// Carlos Maziero, 2015

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// operating system check
#if defined(_WIN32) || (!defined(__unix__) && !defined(__unix) &&              \
                        (!defined(__APPLE__) || !defined(__MACH__)))
#warning Este codigo foi planejado para ambientes UNIX (LInux, *BSD, MacOS). A compilacao e execucao em outros ambientes e responsabilidade do usuario.
#endif

// estrutura que define um tratador de sinal (deve ser global ou static)
struct sigaction action;

const int signals[] = {SIGINT, SIGUSR1};

/* função que tratará os sinais recebidos */
void tratador(int signum) { printf("Recebi o sinal %d\n", signum); }

int main(void) {
  // registra a handler para o sinal SIGINT
  action.sa_handler = tratador;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;

  for (int i = 0; i < 2; i++) {
    if (sigaction(signals[i], &action, 0) < 0) {
      perror("Erro em sigaction: ");
      exit(1);
    }
  }

  /* laço vazio */
  while (1)
    ;
}
