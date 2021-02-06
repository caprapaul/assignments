from clisys import clisys
from undirected_graph import UndirectedGraph
from service import Service


class UI(clisys.CLISys):
    def __init__(self, graph: UndirectedGraph, service: Service):
        super().__init__()
        self.__graph = graph
        self.__service = service

    @clisys.command(name='1', description='Display vertices.')
    def display_vertices(self, args):
        output = ""
        for vertex in self.__graph.parse_vertices():
            output += f"{vertex} "

        print(output)

    @clisys.command(name='2', description='Display edges.')
    def display_edges(self, args):
        output = ""
        for edge in self.__graph.parse_edges():
            output += f"{edge.start} {edge.end} {edge.cost}\n"

        print(output)

    @clisys.command(name='3', description='Add vertex.')
    def add_vertex(self, args):
        vertex = int(input("Input vertex: "))
        self.__graph.add_vertex(vertex)

    @clisys.command(name='4', description='Add edge.')
    def add_edge(self, args):
        edge = input("Input edge('start,end,cost'): ")
        (start, end, cost) = edge.split(",")

        from_vertex = int(start)
        to_vertex = int(end)
        cost = int(cost)

        self.__graph.add_edge(from_vertex, to_vertex, cost)

    @clisys.command(name='5', description='Get degree.')
    def get_degree(self, args):
        vertex = int(input("Input vertex: "))
        in_degree = self.__graph.degree(vertex)
        print(f"Degree: {in_degree}")

    @clisys.command(name='7', description='Display the edges of a vertex.')
    def display_outbound(self, args):
        vertex = int(input("Input vertex: "))
        output = ""
        for edge in self.__graph.parse_vertex_edges(vertex):
            output += f"{edge.start} {edge.end} {edge.cost}\n"

        print(output)

    @clisys.command(name='9', description='Get the cost of an edge.')
    def get_cost(self, args):
        edge = input("Input edge('start,end'): ")
        (start, end) = edge.split(",")

        from_vertex = int(start)
        to_vertex = int(end)

        edge = self.__graph.get_edge(from_vertex, to_vertex)
        print(edge.cost)

    @clisys.command(name='10', description='Set the cost of an edge.')
    def set_cost(self, args):
        edge = input("Input edge('start,end'): ")
        (start, end) = edge.split(",")

        from_vertex = int(start)
        to_vertex = int(end)

        edge = self.__graph.get_edge(from_vertex, to_vertex)

        new_cost = int(input("Input new cost: "))
        edge.cost = new_cost

    @clisys.command(name='11', description='Remove vertex.')
    def remove_vertex(self, args):
        vertex = int(input("Input vertex: "))
        self.__graph.remove_vertex(vertex)

    @clisys.command(name='12', description='Remove edge.')
    def remove_edge(self, args):
        edge = input("Input edge('start,end'): ")
        (start, end) = edge.split(",")

        from_vertex = int(start)
        to_vertex = int(end)

        self.__graph.remove_edge(from_vertex, to_vertex)

    @clisys.command(name='13', description='Get minimum vertex cover.')
    def min_vertex_cover(self, args):
        min_cover = self.__service.get_minimum_vertex_cover()

        if not min_cover:
            print("Cannot find any vertex cover")

        else:
            print(f"Minimum vertex cover: {min_cover}")

    @clisys.command(name='-1', description='Exit.')
    def exit_program(self, args):
        """
        Exits the program.
        """
        self.exit()

    @clisys.exception_handler
    def handle_exceptions(self, exception: Exception):
        """
        Handles exceptions raised in commands.
        :param exception: The exception.
        :return:
        """
        try:
            raise exception

        except clisys.InvalidCommand as e:
            print(f'Invalid option: "{str(e.command_name)}" .')

        except clisys.InvalidArgument as e:
            print(f'Invalid argument: "{str(e.argument_name)}" .')

        except clisys.InvalidArgumentCount:
            print('Invalid argument count.')

        except ValueError as e:
            print(e)

    def display_options(self):
        """
        Displays the list of options.
        :return:
        """
        print()
        options = list(self.get_commands().values())
        options.sort(key=lambda op: int(op.name))

        for option in options:
            print(f'{"%3d" % int(option.name)}. {option.description}')

    @clisys.input_handler
    def get_option(self):
        """
        Gets the input and returns it as a list
        :return: A list of strings. (first element is the name of the command)
        """
        self.display_options()
        i = input('\nOption: ')

        return [i]

