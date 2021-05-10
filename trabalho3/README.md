# FSE - Trabalho Final

## Dados

| Aluno | Matrícula |
| --- | --- |
| Pedro Igor | 17/0062635 |
| Alexandre Miguel Rodrigues Nunes Pereira | 16/0000840 |

## Introdução

O Projeto em questao busca realizar a implementação de um sistema de controle, com um computador atuando como um **Sistema Central** e um conjunto de placas ESP-32 atuando como um **Controlador Distribuido**, cada, através de uma conexão  via Wifi por meio do protocolo MQTT, como descrito no repositório do projeto em [https://gitlab.com/fse_fga/projetos_2020_2/trabalho-final-2020-2](https://gitlab.com/fse_fga/projetos_2020_2/trabalho-final-2020-2).

## Dependências

* [Biblioteca ESP32-DHT11](https://github.com/0nism/esp32-DHT11)

## Execução

Para executar o programa basta clonar o repositório presente...

### Servidor Central

``` bash
# Clone do repositório
$ git clone https://github.com/pedroeagle/fse

# Vá para o diretório do projeto
$ cd fse/trabalho3/

# Relize o build o projeto
$ make

# Inicie a execução
$ make run
```

Com a execução do comando ```make``` é esperado o seguinte resultado:

![imagem1](./images/make_serv_central.png)

Após isso, aparecerá o terminal interativo, com a atualização - em média a cada 1 segundo - dos dados de temperatura sendo obtidos através da conexão com o servidor distribuido, quando estabelecida.

![imagem2](./images/estado_inicial_central.png)


#### ***Painel de Controle***

O Menu contém com um painel de controle seletor de opções, indicado no canto inferior direito, sendo essas opções atualizadas dinâmicamente de acordo com o estado do dispositivo que o usuário deseja acionar:


## Referências

- [Driver da Bosh para o sensor BME280](https://github.com/BoschSensortec/BME280_driver)  
- [Biblioteca BCM2835 - GPIO](http://www.airspayce.com/mikem/bcm2835/)    
- [Biblioteca WiringPi GPIO](http://wiringpi.com)  
- [PWM via WiringPi](https://www.electronicwings.com/raspberry-pi/raspberry-pi-pwm-generation-using-python-and-c)
