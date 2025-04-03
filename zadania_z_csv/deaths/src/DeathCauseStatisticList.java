import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class DeathCauseStatisticList {
    public List<DeathCauseStatistic> list;

    public void repopulate(String path){
        try{
            list = Files.lines(Paths.get(path))
                    .skip(2)
                    .map(DeathCauseStatistic::fromCsvLine)
                    .toList();

            int age = 34;
            list.stream().sorted(
                    (x, y) -> Integer.compare(
                            y.ageBracket(age).deathCount,
                            x.ageBracket(age).deathCount
                    )
            ).collect(Collectors.toList()).subList(0, n);

        } catch (IOException e){
            throw new RuntimeException();
        }
    }

    public List<DeathCauseStatistic> mostDeadlyDiseases(int age, int n){
        List<DeathCauseStatistic> = new ArrayList();

    }
}















public List<DeathCauseStatistics> mostDeadlyDiseases(int age, int n)
{
        /*List<DeathCauseStatistics> results = new ArrayList<>();
        for(DeathCauseStatistics currentStat : stats){
            results.add(currentStat.getDeathsForAge(age));
        }*/
    List<DeathCauseStatistics> results = new ArrayList<>(stats);
    results.sort((disease1, disease2)->Integer.compare(
            disease1.getDeathsForAge(age).deathCount(),
            disease2.getDeathsForAge(age).deathCount()
    ));
    return results.reversed().subList(0, n);
}
