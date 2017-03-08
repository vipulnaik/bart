import com.petametrics.api.util._
import scala.util.Try

val monthfull = "2016-02"
val path = s"/Users/admin/gitcode/bart/ridership/$monthfull/weekday.csv"

val data = File.readString(path).split("\n") // Using library used at work; replace with generic Scala file reader

val stationCodes = data(1).tail.split(",").filter(_.size == 2)

val stationMap = data.dropRight(2).map(x => x.split(",").head -> (stationCodes zip x.split(",").tail)).toMap

val stationMapFixed = stationMap.mapValues(_.map{case (a,b) => (a,Try(b.filter(t => Character.isDigit(t)).toInt).getOrElse(0))})

val stationOutputString = stationCodes.map(exitStationCode => {
  stationMapFixed.getOrElse(exitStationCode, Array()).toSeq.map{
    case (entryStationCode, count) => s"""('$monthfull','$entryStationCode','$exitStationCode',$count)"""
  }
}).flatten.mkString(",\n")

val preamble = """insert into ridership(monthfull,entry_station_code,exit_station_code,count) values \n"""

val queryString = preamble + stationOutputString + ";"

println(queryString)
