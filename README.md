# Rope OpenGL

Projeto acadêmico de Computação Gráfica com OpenGL clássico e FreeGLUT. A cena reúne um personagem articulado, uma bola com física, terreno em blocos, câmera orbital, iluminação, texturas e interação por teclado e mouse. A implementação mantém a matriz fixa e a pilha de transformações para deixar os conceitos estudados visíveis.

## Dependências

- CMake 3.16 ou mais recente
- Compilador C++17 (GCC, Clang ou MSVC)
- OpenGL, GLU e FreeGLUT

No MSYS2 UCRT64, instale com:

```sh
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-freeglut
```

No Ubuntu/Debian:

```sh
sudo apt install build-essential cmake freeglut3-dev libglu1-mesa-dev
```

## Compilar

Execute na raiz do repositório:

```sh
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_PREFIX_PATH=C:/msys64/ucrt64 -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

Com Visual Studio no Windows, use `cmake -S . -B build` e depois `cmake --build build --config Release --parallel`.

No Windows, execute `build/rope-opengl.exe`; em Linux e macOS, `build/rope-opengl`. Rode o aplicativo com a raiz do repositório como diretório atual para que as texturas em `src/` sejam encontradas.

O projeto habilita `-Wall -Wextra -Wpedantic` no GCC/Clang e `/W4` no MSVC. O código de terceiros `stb_image` não participa dos avisos do projeto.

## Controles

- `W`, `A`, `S`, `D`: mover o personagem (diagonal com velocidade normalizada)
- `Espaço`: pular
- Botão do meio pressionado e arraste: orbitar a câmera
- Roda do mouse: aproximar ou afastar
- Clique esquerdo e arraste a bola: reposicionar mantendo a altura inicial do arraste
- Setas: mover a luz
- `+` / `-`: ajustar iluminação
- Botão direito: menu com celebração, reset e saída
- `Esc`: sair

## Notas de implementação

A bola e o personagem usam o mesmo modelo de física, cada um com um único estado de posição e velocidade. A simulação é avançada em passos fixos de 1/120 s e o amortecimento horizontal é exponencial em função do tempo. A bola colide com o piso como esfera; o personagem usa um ponto de apoio para o contato vertical e uma cápsula aproximada para detectar contato com a bola.

A aplicação segue usando funções tradicionais do OpenGL (matrizes, materiais, quadricas e iluminação fixa) como recurso didático. Ela não depende de shaders nem de uma pipeline moderna.

## Verificações automatizadas

Os testes cobrem altura e limites do terreno, repetibilidade da simulação, contato da bola com o piso e velocidade diagonal. Rode `ctest --test-dir build --build-config Release --output-on-failure` (troque `Release` por `Debug` se compilou essa configuração).
