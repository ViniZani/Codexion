# Codexion

*This project has been created as part of the 42 curriculum by vzani-st.*

---

## Description
**Codexion** is a project focused on solve the Philosophers's Dinner Problemns, handling threads, and the situations that this concepts brings, like Deadlock and Race Condicion. There is a table, with a num of coder, and each coder has one dongle in your side. Each coder have a routine: compile, debug, refacto. But, for do this routine each coder need 2 dongles, one in each hand. After he refacto, he drops the tww dongles on the table again, for other coder use.

## Instructions
This project needs to recieve 8 parameters necessarily,in order.
- <num_coder>: represents o num of coders i the table 
- <time_to_burnout>: represents, in ms, the time that coders will burn out
- <time_to_compile>: represents, in ms, the time that coders will compile
- <time_to_debug>: represents, in ms, the time that coders will debug 
- <time_to_refactor>: represents, in ms, the time that coders will refacto 
- <number_of_compiles_required>: represents the num of compiles that coders will need to compile necessarily 
- <dongle_cooldown>: represents, in ms, the time that dongles will wait after they can used again 
- <scheduler>: represetns the policy used by dongles to decide who gets them
when multiple coders request them (must be fifo or edf)
### Running the project
The project uses a `Makefile` to facilitate setup across different operating systems.

```bash
# To compile:
make
```
### Execution
To run this program, you will need pass necessarily 8 parameters:

```bash
./codexion <num_coder> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```
### Blocking cases handled
#### 1.Deadlock
The main comcept and the main challenger. The Deadlock occurs when 
### Thread synchronization mechanisms


## Resources
- Wikipedia: Dijskra Algorithm

- Algoritmo do Caminho Mais Curto de Dijkstra | Teoria dos Grafos- https://www.youtube.com/watch?v=pSqmAO-m7Lk&t=28sk

- Algoritmo de Busca em Largura | Caminho Mais Curto | Teoria dos Grafos - https://www.youtube.com/watch?v=oDqjPvD54Ss


- Como Criar uma Interface Gráfica Python c/ CustomTkinter [RÁPIDO]- https://www.youtube.com/watch?v=Px-DgrQ_wjI

- Breadth First Search (BFS): Visualized and Explained - https://www.youtube.com/watch?v=xlVX7dXLS64&t=45s


- 5.1 Graph Traversals - BFS & DFS -Breadth First Search and Depth First Search - https://www.youtube.com/watch?v=pcKY4hjDrxk

### AI Usage
Artificial Intelligence was utilized in this project for the following tasks:

Code Refactoring: Assistance in converting functions to meet rigorous Flake8 and Mypy standards (linting).

Environment Bug Fixing: Diagnosing compatibility errors between Unix Makefiles and Windows PowerShell.

Documentation: Initial structuring of Docstrings following the PEP 257 standard.

Optimization: Used to anwser pontual questions.