using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace lab_06
{
    public class DirectedGraph
    {
        private readonly List<List<int>> _edges;

        public DirectedGraph(int nodeCount)
        {
            _edges = new List<List<int>>(nodeCount);
            Nodes = new List<int>();

            for (var i = 0; i < nodeCount; i++)
            {
                _edges.Add(new List<int>());
                Nodes.Add(i);
            }

            GenerateRandomHamiltonian(2 * nodeCount);
        }

        public List<int> Nodes { get; }

        private void GenerateRandomHamiltonian(int size)
        {
            size -= Nodes.Count;
            Nodes.Shuffle();

            for (var i = 0; i < Nodes.Count - 1; i++)
            {
                AddEdge(Nodes[i], Nodes[i + 1]);
            }

            AddEdge(Nodes[^1], Nodes[0]);

            for (var i = 0; i < size; i++)
            {
                var a = ProgramRandom.Instance.Next(Nodes.Count);
                var b = ProgramRandom.Instance.Next(Nodes.Count);

                AddEdge(a, b);
            }
        }

        public void AddEdge(int a, int b)
        {
            _edges[a].Add(b);
        }

        public List<int> NeighboursOf(int node)
        {
            return _edges[node];
        }

        public List<int> GetHamiltonianCycle()
        {
            var result = new List<int>();
            var found = false;

            void Visit(int startingNode)
            {
                var path = new List<int>(Nodes.Count);
                var nextNodes = new Stack<int>();
                nextNodes.Push(startingNode);

                while (nextNodes.Count > 0)
                {
                    var currentNode = nextNodes.Pop();
                    path.Add(currentNode);

                    if (found)
                    {
                        return;
                    }

                    if (path.Count == Nodes.Count)
                    {
                        if (!NeighboursOf(currentNode).Contains(startingNode))
                        {
                            return;
                        }

                        found = true;

                        lock (result)
                        {
                            result.Clear();
                            result = new List<int>(path);
                        }

                        return;
                    }

                    foreach (var neighbour in NeighboursOf(currentNode))
                    {
                        if (!path.Contains(neighbour))
                        {
                            nextNodes.Push(neighbour);
                        }
                    }
                }
            }

            Parallel.ForEach(Nodes, Visit);

            return result;
        }

        public override string ToString()
        {
            var edges = _edges.Select((e, i) => $"{i}: {string.Join(',', e)}");
            var edgesString = string.Join('\n', edges);

            return "DirectedGraph {" +
                   "\nnodes:\n" +
                   string.Join(',', Nodes) +
                   "\n\nedges:\n" +
                   edgesString +
                   "\n}";
        }
    }
}
