val path = "/Users/admin/gitcode/bart/ridership/2016-02/weekday.csv"

val data = File.readString(path).split("\n") // Using library used at work; replace with generic Scala file reader

val stationCodes = data(1).tail.split(",").filter(_.size == 2)

val stationMap = data.dropRight(2).map(x => x.split(",").head -> (stationCodes zip x.split(",").tail)).toMap

