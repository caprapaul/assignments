from clisys import clisys
from cmdsys import cmdsys
from repositories.repository import RepositoryError
from services.activity_service import ActivityService, ActivityServiceError
from services.person_service import PersonService, PersonServiceError
from models.person import Person
from models.activity import Activity

import datetime


class UIError(Exception):
    def __init__(self, message):
        super().__init__(message)


class UI(clisys.CLISys):
    def __init__(self, person_service: PersonService, activity_service: ActivityService):
        super().__init__()
        self.__person_service = person_service
        self.__activity_service = activity_service

    def input_person(self, uid: str):
        name = input('Input person name: ')
        phone_number = input('Input person phone number: ')

        return Person(uid, name, phone_number)

    @clisys.command(name='100', description='Undo.')
    def undo(self, args):
        """
        Undo the last command that changed the expenses list.
        :param args:
        :return:
        """
        cmdsys.CommandSystem.global_undo()
        print('Undo executed successfully!')

    @clisys.command(name='200', description='Redo.')
    def redo(self, args):
        """
        Undo the last command that changed the expenses list.
        :param args:
        :return:
        """
        cmdsys.CommandSystem.global_redo()
        print('Redo executed successfully!')

    @clisys.command(name='11', description='Add person.')
    def add_person(self, args):
        """
        Adds a person.
        """
        person = self.input_person(self.__person_service.generate_uid())
        self.__person_service.add_person(person)

    @clisys.command(name='12', description='Display persons.')
    def display_persons(self, args):
        """
        Displays person.
        """
        persons = self.__person_service.get_persons()
        print('UID \t|\tPhone Number |\tName')

        for person in persons:
            print(person)

    @clisys.command(name='13', description='Remove person.')
    def remove_person(self, args):
        uid = input('Input person uid: ')

        self.__person_service.remove_person(uid)
        print('Person removed successfully!')

    @clisys.command(name='14', description='Update person.')
    def update_person(self, args):
        uid = input('Input person uid: ')
        old_person: Person = self.__person_service.get_person(uid)

        print('New person data:')
        new_person = self.input_person(self.__person_service.generate_uid())

        new_name = old_person.name if new_person.name == '' else new_person.name
        new_phone_number = old_person.phone_number if new_person.phone_number == '' else new_person.phone_number

        new_person = Person(uid, new_name, new_phone_number)

        self.__person_service.update_person(uid, new_person)
        print('Person updated successfully!')

    @clisys.command(name='15', description='Search persons.')
    def search_person(self, args):
        name = input('Input person name: ')
        phone_number = input('Input person phone number: ')

        persons = self.__person_service.search_persons(name, phone_number)

        for person in persons:
            print(person)

    def input_activity(self, uid: str):
        date_raw = input('Input activity date (yyyy-mm-dd): ')
        time_raw = input('Input activity time (HH:MM:')

        date = None

        if date_raw != '':
            date = datetime.datetime.strptime(date_raw, '%Y-%m-%d').date()

        time = None

        if time_raw != '':
            time = datetime.datetime.strptime(time_raw, '%H:%M').time()

        description = input('Input activity description: ')
        persons_uids = input('Input activity persons: <uid_1>,<uid_2>,...\n').split(',')

        return Activity(uid, persons_uids, date, time, description)

    @clisys.command(name='21', description='Add activity.')
    def add_activity(self, args):
        """
        Adds an activity.
        """
        activity = self.input_activity(self.__activity_service.generate_uid())
        self.__activity_service.add_activity(activity)

    @clisys.command(name='22', description='Display activities.')
    def display_activities(self, args):
        activities = self.__activity_service.get_activities()
        print('UID \t|\tDate\t\t|\tTime\t\t|\tDesc.\t|\tPersons UIDs')

        for activity in activities:
            print(activity)

    @clisys.command(name='23', description='Remove activity.')
    def remove_activity(self, args):
        uid = input('Input activity uid: ')

        self.__activity_service.remove_activity(uid)
        print('Activity removed successfully!')

    @clisys.command(name='24', description='Update activity.')
    def update_activity(self, args):
        uid = input('Input activity uid: ')
        old_activity: Activity = self.__activity_service.get_activity(uid=uid)

        print('New activity data:')
        new_activity = self.input_activity(uid)

        new_date = old_activity.date if new_activity.date is None else new_activity.date
        new_time = old_activity.time if new_activity.time is None else new_activity.time
        new_description = old_activity.description if new_activity.description == '' else new_activity.description

        if not new_activity.persons_uids:
            new_persons_uids = old_activity.persons_uids

        else:
            new_persons_uids = old_activity.persons_uids + new_activity.persons_uids

        new_activity = Activity(uid, new_persons_uids, new_date, new_time, new_description)

        self.__activity_service.update_activity(uid, new_activity)
        print('Activity updated successfully!')

    @clisys.command(name='25', description='Search activities.')
    def search_activities(self, args):
        date_raw = input('Input activity date (yyyy-mm-dd): ')
        time_raw = input('Input activity time (HH:MM:')

        date = None

        if date_raw != '':
            date = datetime.datetime.strptime(date_raw, '%Y-%m-%d').date()

        time = None

        if time_raw != '':
            time = datetime.datetime.strptime(time_raw, '%H:%M').time()

        description = input('Input activity description: ')

        activities = self.__activity_service.search_activities(date, time, description)

        for activity in activities:
            print(activity)

    @clisys.command(name='26', description='Display the activities for a date.')
    def display_date_activities(self, args):
        date_raw = input('Input date (yyyy-mm-dd): ')
        date = datetime.datetime.strptime(date_raw, '%Y-%m-%d').date()
        activities = self.__activity_service.get_date_activities(date)

        print('UID \t|\tDate\t\t|\tTime\t\t|\tDesc.\t|\tPersons UIDs')
        for activity in activities:
            print(activity)

    @clisys.command(name='27', description='Display the busiest days.')
    def display_busiest_days(self, args):
        days = self.__activity_service.get_busiest_days()

        print('Date\t\t|\tActivities Count')
        for day in days:
            print(f'{day[0]}\t\t{day[1]}')

    @clisys.command(name='28', description='Display activities with a person.')
    def display_person_activities(self, args):
        person_uid = input('Input person uid: ')
        activities = self.__activity_service.get_person_activities(person_uid)

        print('UID \t|\tDate\t\t|\tTime\t\t|\tDesc.\t|\tPersons UIDs')
        for activity in activities:
            print(activity)

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

        except cmdsys.EmptyActionsStack:
            print('Nothing to undo.')

        except cmdsys.EmptyUndoStack:
            print('Nothing to redo.')

        except ActivityServiceError as e:
            print(e)

        except PersonServiceError as e:
            print(e)

        except RepositoryError as e:
            print(e)

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

