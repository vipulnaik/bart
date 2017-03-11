import com.petametrics.api.util._
import scala.util.Try

val sb = new StringBuilder
for (year <- 2000 to 2017) {
  for (month <- 1 to 12) {
    val monthfull = s"$year-" + "%02d".format(month)
    for (dayType <- Seq("weekday", "saturday", "sunday")) try {
      val path = s"/Users/admin/gitcode/bart/ridership/$monthfull/$dayType.csv"
      val data = File.readString(path).split("\n") // Using library used at work; replace with generic Scala file reader

      val stationCodes = data(1).tail.split(",").filter(_.size == 2)

      val stationMap = data.dropRight(2).map(x => x.split(",").head -> (stationCodes zip x.split(",").tail)).toMap

      val stationMapFixed = stationMap.mapValues(_.map{case (a,b) => (a,Try(b.filter(t => Character.isDigit(t)).toInt).getOrElse(0))})

      val stationOutputString = stationCodes.map(exitStationCode => {
        stationMapFixed.getOrElse(exitStationCode, Array()).toSeq.map{
          case (entryStationCode, count) => s"""('$monthfull','$dayType','$entryStationCode','$exitStationCode',$count)"""
        }
      }).flatten.mkString(",\n")

      val preamble = """insert ignore into ridership(monthfull,day_type,entry_station_code,exit_station_code,day_type,count) values \n"""

      val queryString = preamble + stationOutputString + ";"

      sb ++= queryString + "\n"
    } catch {
      case e: Exception => println(s"Encountered error on year $year and month $month")
    }
  }
}

File.writeString(sb.toString(), "/Users/admin/gitcode/bart/ridership/insertions.sql")
