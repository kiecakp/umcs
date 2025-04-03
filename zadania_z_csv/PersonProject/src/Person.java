import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

public class Person {
    public String name;
    public LocalDate birthDate;
    public LocalDate deathDate;

    public static Person fromCsvLine(String line){
        String[] splited = line.split(",");

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd.MM.yyyy");
        LocalDate date = LocalDate.parse(splited[1], formatter);

        Person person = new Person();
        person.name = splited[0];
        person.birthDate = date;
        if(!splited[2].isEmpty()){
            person.deathDate = LocalDate.parse(splited[2], formatter);
        }

        return person;
    }

    public static List<Person> fromCsv(String path){
        ArrayList<Person> list = new ArrayList<>();

        try {
            FileReader file = new FileReader(path);
            BufferedReader reader = new BufferedReader(file);
            String line = reader.readLine();    // linia naglowkowa
            line = reader.readLine();   // pierwsze dane

            while(line != null){
                Person person = fromCsvLine(line);
                try {
                    person.checkLifespan();
                    person.checkAmbiguousPersonException(list);
                } catch (NegativeLifespanException | AmbiguousPersonException e) {
                    System.out.println(e.getMessage());
                }

                list.add(person);
                line = reader.readLine();
            }
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        return list;
    }

    public void checkLifespan() throws NegativeLifespanException {
        if(deathDate != null && deathDate.isBefore(birthDate)){
            throw new NegativeLifespanException(this);
        }
    }
    public void checkAmbiguousPersonException(List<Person> list) throws AmbiguousPersonException {
        for(Person person : list){
            if(person.name.equals(this.name)){
                throw new AmbiguousPersonException(this);
            }
        }
    }
}
