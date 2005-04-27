# $ willedu - willedu@users.sourceforge.net $

# compilador e opcoes gerais
CC	:= g++
CFLAGS	:= -Wall -O2

# alterar caso “strip” nao esteja no path atual
#STRIP	:= strip

# o resultado da compilacao

SRCDIR  := /src/atena
OBJDIR  := /obj/gcc/atena

BINARY	:= teste.exe
BINDIR	:= /bin
BINPATH	:= $(BINDIR)/$(BINARY)

# adicionar objetos caso necessario
OBJS 	:= calien.o \
	   carma.o \
	   cbonus.o \
	   ccenario.o \
	   cchefe.o \
	   ccolecao.o \
	   cconstrucao.o \
	   cexplosao.o \
	   cfase.o \
	   cfilme.o \
	   cfundo.o \
	   cinimigo.o \
	   cjogo.o \
	   cladrilho.o \
	   cmenu.o \
	   cnave.o \
	   cobjeti.o \
	   ctela.o \
	   ctiro.o \
	   cveiculo.o \
	   erro.o \
	   main.o


# alvo padrao, executar para compilar o programa

all: $(BINARY)
	$(STRIP) $(BINARY)

$(BINARY): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $?

$(OBJS): %.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


# alvo de limpeza, executar para remover os arquivos gerados
# durante a compilacao

clean:
	del $(OBJS)
	del $(BINARY)

# alvo de instalacao, executar como administrador!
install: all
	copy $(BINARY) $(BINDIR)
#	chown 0.0 $(BINPATH)