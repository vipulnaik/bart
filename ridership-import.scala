import scala.util.Try
import java.util.Date

val forbiddenStationCodes = Nil
for (year <- 2001 to 2023) {
  println(s"${new Date(System.currentTimeMillis()).toString} Started processing year $year")
  val sb = new StringBuilder
  for (month <- 1 to 12) {
    val monthfull = s"$year-" + "%02d".format(month)
    for (dayType <- Seq("weekday", "saturday", "sunday")) try {
      val path = s"/Users/vipulnaik/git/personal-public/bart/ridership/$monthfull/$dayType.csv"
      println(s"${new Date(System.currentTimeMillis()).toString} Processing path $path")
      val data = scala.io.Source.fromFile(path).mkString.split("\n")

      val stationCodes = data(1).tail.split(",").map(_.filter(t => Character.isLetterOrDigit(t))).filter(_.size == 2)

      val stationMap = data.drop(2).dropRight(1).map(x => x.split(",").head -> (stationCodes zip x.split(", ").map(_.split(""","""")).flatten.map(_.split("""",""")).flatten.tail)).toMap

      val stationMapFixed = stationMap.mapValues(_.map{case (a,b) => (a,Try(b.filter(t => Character.isDigit(t)).toInt).getOrElse(0))})

      val stationOutputString = stationCodes.filter(x => !forbiddenStationCodes.contains(x)).map(exitStationCode => {
        stationMapFixed.getOrElse(exitStationCode, Array()).toSeq
          .filter{case (entryStationCode, count) => !forbiddenStationCodes.contains(entryStationCode)}
          .map{
          case (entryStationCode, count) => s"""('$monthfull','$dayType','$entryStationCode','$exitStationCode',$count)"""
        }
      }).flatten.mkString(",\n")

      val preamble = """insert ignore into ridership(monthfull,day_type,entry_station_code,exit_station_code,rider_count) values""" + "\n"

      val queryString = preamble + stationOutputString + ";"

      sb ++= queryString + "\n"
    } catch {
      case e: Exception => println(s"Encountered error ${e.toString} on year $year and month $month, stack trace ${e.getStackTrace.take(20).mkString("\n")}")
    }
  }
  val outputPath = s"/Users/vipulnaik/git/personal-public/bart/ridership/insertions-$year.sql"
  println(s"${new Date(System.currentTimeMillis()).toString} Going to write to $outputPath")
  val file = new java.io.File(outputPath)
  file.getParentFile.mkdirs
  val pw = new java.io.PrintWriter(file)
  pw.write(sb.toString())
  pw.close
  println(s"${new Date(System.currentTimeMillis()).toString} Finished writing to $outputPath")
  println(s"${new Date(System.currentTimeMillis()).toString} Finished processing year $year")
}

for (year <- 2024 to 2024) {
  println(s"${new Date(System.currentTimeMillis()).toString} Started processing year $year")
  val sb = new StringBuilder
  for (month <- 1 to 7) {
    val monthfull = s"$year-" + "%02d".format(month)
    for (dayType <- Seq("weekday", "saturday", "sunday")) try {
      val path = s"/Users/vipulnaik/git/personal-public/bart/ridership/$monthfull/$dayType.tsv"
      println(s"${new Date(System.currentTimeMillis()).toString} Processing path $path")
      val data = scala.io.Source.fromFile(path).mkString.split("\n")

      val stationCodes = data(4).split("\t").tail.map(_.filter(t => Character.isLetterOrDigit(t))).filter(_.size == 2)

      val stationMap = data.drop(5).dropRight(1).map(x => x.split("\t").head -> (stationCodes zip x.split("\t").tail.dropRight(1))).toMap

      val stationMapFixed = stationMap.mapValues(_.map{case (a,b) => (a,Try(b.filter(t => Character.isDigit(t)).toInt).getOrElse(0))})

      val stationOutputString = stationCodes.filter(x => !forbiddenStationCodes.contains(x)).map(exitStationCode => {
        stationMapFixed.getOrElse(exitStationCode, Array()).toSeq
          .filter{case (entryStationCode, count) => !forbiddenStationCodes.contains(entryStationCode)}
          .map{
          case (entryStationCode, count) => s"""('$monthfull','$dayType','$entryStationCode','$exitStationCode',$count)"""
        }
      }).flatten.mkString(",\n")

      val preamble = """insert ignore into ridership(monthfull,day_type,entry_station_code,exit_station_code,rider_count) values""" + "\n"

      val queryString = preamble + stationOutputString + ";"

      sb ++= queryString + "\n"
    } catch {
      case e: Exception => println(s"Encountered error ${e.toString} on year $year and month $month, stack trace ${e.getStackTrace.take(20).mkString("\n")}")
    }
  }
  val outputPath = s"/Users/vipulnaik/git/personal-public/bart/ridership/insertions-$year.sql"
  println(s"${new Date(System.currentTimeMillis()).toString} Going to write to $outputPath")
  val file = new java.io.File(outputPath)
  file.getParentFile.mkdirs
  val pw = new java.io.PrintWriter(file)
  pw.write(sb.toString())
  pw.close
  println(s"${new Date(System.currentTimeMillis()).toString} Finished writing to $outputPath")
  println(s"${new Date(System.currentTimeMillis()).toString} Finished processing year $year")
}
