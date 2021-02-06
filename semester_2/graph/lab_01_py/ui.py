from clisys import clisys
from directed_graph import DirectedGraph
from service import Service


class UI(clisys.CLISys):
    def __init__(self, graph: DirectedGraph, service: Service):
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

    @clisys.command(name='5', description='Get in degree.')
    def get_in_degree(self, args):
        vertex = int(input("Input vertex: "))
        in_degree = self.__graph.in_degree(vertex)
        print(f"In degree: {in_degree}")

    @clisys.command(name='6', description='Get out degree.')
    def get_out_degree(self, args):
        vertex = int(input("Input vertex: "))
        out_degree = self.__graph.out_degree(vertex)
        print(f"Out degree: {out_degree}")

    @clisys.command(name='7', description='Display inbound edges of a vertex.')
    def display_outbound(self, args):
        vertex = int(input("Input vertex: "))
        output = ""
        for edge in self.__graph.parse_in(vertex):
            output += f"{edge.start} {edge.end} {edge.cost}\n"

        print(output)

    @clisys.command(name='8', description='Display outbound edges of a vertex.')
    def display_inbound(self, args):
        vertex = int(input("Input vertex: "))
        output = ""
        for edge in self.__graph.parse_out(vertex):
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

    @clisys.command(name='13', description='Get shortest path between vertices.')
    def display_path(self, args):
        start_vertex = int(input("Input start vertex: "))
        end_vertex = int(input("Input end vertex: "))

        path = self.__service.get_path(start_vertex, end_vertex)

        if not path:
            print("Path not possible.")
        else:
            print(f"The path from {start_vertex} to {end_vertex}: {path}.")

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

