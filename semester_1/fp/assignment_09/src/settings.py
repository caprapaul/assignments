class Settings:
    def __init__(self):
        self.__props = {}
        self.load_settings()

    def load_settings(self):
        with open('settings.properties', 'r') as settings:
            for prop in settings:
                prop = prop.strip()

                if len(prop) == 0:
                    continue

                name, value = prop.split('=')
                name = name.strip()
                value = value.strip().replace('"', '')
                self.__props[name] = value

    @property
    def repository(self):
        return self.__props.get('repository')

    @property
    def persons(self):
        return self.__props.get('persons')

    @property
    def activities(self):
        return self.__props.get('activities')