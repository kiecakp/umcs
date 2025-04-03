import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
//   ----------- test metody Person.fromCsv -------------------
        List<Person> list = Person.fromCsv("family.csv");
        for(Person person : list){
            System.out.println(person.name);
        }
    }
}