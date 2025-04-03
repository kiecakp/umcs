public class DeathCauseStatistic {
    private String kod_ic10;
    private int[] deaths;

    public String getKod_ic10() {
        return kod_ic10;
    }

    public static DeathCauseStatistic fromCsvLine(String line){
        DeathCauseStatistic result = new DeathCauseStatistic();

        String[] splited = line.split(",");
        result.kod_ic10 = splited[0];
        result.kod_ic10.trim();
        result.deaths = new int[20];
        for(int i = 2, j = 0; i < 20; i++, j++){
            if(splited[i].equals("-")){
                result.deaths[j] = 0;
            } else{
                result.deaths[j] = Integer.parseInt(splited[i]);
            }
        }
        return result;
    }

    public AgeBracketDeaths ageBracket(int age){
        int young, old, deathCount;
        if(age >= 95){
            young = 95;
            old = Integer.MAX_VALUE;
            deathCount = deaths[19];
        } else {
            int index = (age / 5) + 1;
            young = (age/5) * 5;
            old = young + 4;
            deathCount = deaths[index];
        }
        return new AgeBracketDeaths(young, old, deathCount);
    }

    public class AgeBracketDeaths{
        public final int young;
        public final int old;
        public final int deathCount;

        public AgeBracketDeaths(int young, int old, int deathCount) {
            this.young = young;
            this.old = old;
            this.deathCount = deathCount;
        }
    }


}
