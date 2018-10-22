
void printData(struct person *person)
{
  switch (person->staff_or_student) {
    case 0:  // staff
      printf("Staff's   name: %-10s age: %-7d Room number: %s\n" , person->name, person->age, person->extraInfo.room_number);
      break;
    case 1:  // student
      printf("Student's   name: %-10s age: %-7d Course: %s\n", person->name, person->age, person->extraInfo.programme_name);
      break;
    case 2:  // neither
      printf("Person's   name: %-10s age: %-7d\n", person->name, person->age);
      break;
  }
}
