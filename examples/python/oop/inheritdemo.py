#!/usr/bin/python3

class SchoolMember:
    '''Represents any school member.'''
    def __init__(self, name, age):
        self.name = name
        self.age = age
        print('(Initialized SchoolMember: {0})'.format(self.name))
 
    def tell(self):
        '''Tell my details.'''
        print('Name:"{0}" Age:"{1}"'.format(self.name, self.age), end=" ")
 
class Teacher(SchoolMember):
    '''Represents a teacher.'''
    def __init__(self, name, age, salary):
        super().__init__(name, age)
        self.salary = salary
        print('(Initialized Teacher: {0})'.format(self.name))
 
    def tell(self):
        super().tell()
        print('Salary: "{0:d}"'.format(self.salary))
 
class Student(SchoolMember):
    '''Represents a student.'''
    def __init__(self, name, age, marks):
        super().__init__(name, age)
        self.marks = marks
        print('(Initialized Student: {0})'.format(self.name))
 
    def tell(self):
        super().tell()
        print('Marks: "{0:d}"'.format(self.marks))
 

t = Teacher('Mrs. Abraham', 40, 30000)
s = Student('Swaroop', 21, 75)

print() # prints a blank line

members = [t, s]
for member in members:
        member.tell()
        # Works for instances of Student as well as Teacher
          

