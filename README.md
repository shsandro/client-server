# Client-Proxy-Server

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Resumo da Aplicação

A aplicação é um conjunto de 4 programas, escritos em C, que simulam a comuniação entre um cliente e um servidor, por meio de proxy, em um contexto específico. A aplicação possuirá 3 servidores, cada um com seu propósito específico.

- Linguagens
	- Cliente: C
	- Proxy e Servidores: C

## Contexto

A aplicação fornece um sistema de gerenciamentom de mídias (filmes, músicas e fotos), cada uma armazenada em um servidor diferente. As operações possíveis são:

	- Cadastro e busca de filmes
	- Cadastro e busca de músicas
	- Cadastro e busca de fotos

### Gerenciamento de informações
Todos os modelos (filmes, músicas e fotos) serão armazenados em memória. Para gerenciamento de requisições, serão criados processos por meio de Fork tanto nos servidores quanto no proxy.

	- O servidor de vídeos utilizará Pipe para gerenciamento do acesso ao banco de dados
	- O servidor de músicas utilizará FIFO
	- O servidor de fotos utilizará Memória Compartilhada e Semáforo
    
## Compilação

Para compilação, os possíveis targets são:

	- `client` para compilar o cliente
	- `proxy` para compilar o proxy
	- `video_server` para compilar o servidor de vídeos
	- `music_server` para compilar o servidor de músicas
	- `photo_server` para compilar o servidor de fotos
	- `make` para compilar todo o programa

## Execução

- Para executar os servidores:
	- `./video_server.out`
	- `./music_server.out`
	- `./photo_server.out`
	
- Para executar o proxy:
	- `./proxy.out`
	
- Para executar o cliente:
	- `./client.out`
    
## Desenvolvedores

- [Douglas Ferreira Delefrati](https://github.com/deelefrati)
- [Sandro Henrique Uliana](https://github.com/shsandro)
