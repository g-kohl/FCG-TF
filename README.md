# <p align="center">Bloons 3D 🎈</p>

Trabalho desenvolvido na disciplina de Fundamentos de Computação Gráfica (INF01047) pelos alunos Guilherme Kohl e Matheus Manica.

O objetivo deste trabalho é consolidar o conhecimento sobre os principais conceitos de Computação Gráfica, como visualização em ambientes tridimensionais, interação, detecção de colisão, utilização de texturas, entre outros.
Para isso, foi realizado o desenvolvimento de uma versão em 3D do jogo **Bloons Tower Defense**, totalmente em C/C++ com OpenGL.

## Contribuições de cada membro

O trabalho foi realizado de forma colaborativa entre os membros, cada membro foi responsável por partes distintas do desenvolvimento, porém a visão geral da aplicação foi necessária para ambos.
Além disso, o desenvolvimento da lógica central e certas funcionalidades do jogo foi desenvolvida simultaneamente por ambos.

Matheus:
- Movimento dos balões utilizando curvas de bézier cúbicas.
- Teste de intersecções/colisões dos objetos.
- Animações baseadas em tempo de execução.
- Lógica do jogo e utilitários.

Guilherme:
- Câmera livre e câmera look-at.
- Modelos de Iluminação Difusa e Blinn-Phong.
- Modelos de Interpolação de Phong e Gouraud.
- Mapeamento de texturas dos objetos.
- Lógica do jogo e utilitários

## Uso de LLM

## Uso de conceitos de Computação Gráfica

A aplicação conta com três tipos de objetos instanciáveis: balão, macaco e dardo. Sendo o macaco um objeto que possui dois modelos e pode ser posicionado pelo usuário utilizando transformações geométricas.
Balões, dardo e macaco de nível inicial possuem texturas mapeadas por projeção planar. O macaco de nível superior tem sua textura mapeada por uma projeção esférica.
Além disso, o macaco de nível inicial é interpolado pelo modelo de Gouraud. Os demais objetos utilizam interpolação de Phong.
Além de possuírem malhas poligonais complexas, todas as animações dos objetos são baseados em tempo, utilizando cálculo de delta time de cada objeto.
Os balões, que se movimentam seguindo uma trilha de pontos que são calculados por curvas de bézier cúbicas piecewise, possuem níveis diferentes que são representados por cores distintas. Sua iluminação é calculada utilizando o modelo de Blinn-Phong.
Os demais objetos são iluminados pelo modelo de iluminação difusa.
É possível se mover pela cena livremente utilizando uma free camera ou fixar a câmera do tipo look-at para uma visão superior do cenário.

São realizados quatro tipos de teste de intersecção/colisão:
- Ponto x Esfera: utilizado para detecção de um balão no range de visão de um macaco.
- Bounding Box x Vetor: utilizado na checagem de colisão do dardo com um balão.
- Esfera x Bounding Box: utilizado na colisão da câmera com os macacos.
- Bounding Box x Bounding Box: utilizado para evitar a sobreposição de dois macacos ao posicionalos.
