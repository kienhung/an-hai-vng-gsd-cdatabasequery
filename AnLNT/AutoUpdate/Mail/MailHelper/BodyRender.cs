using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.IO;

namespace MailHelper
{
    class BodyRender
    {
        protected string _header =
            "<!DOCTYPE html> <html> <head> <title>Game Update Report</title> <meta charset=\"utf-8\"> <style> #customers { font-family:\"Trebuchet MS\", Arial, Helvetica, sans-serif; border-collapse:collapse; } #customers td, #customers th { font-size:1em; border:1px solid; padding:3px 7px 2px 7px; } #customers th { font-size:1.1em; text-align:left; padding-top:5px; padding-bottom:4px; background-color:#BDBEB7; } #customers tr.alt td { color:#000000; background-color:#CAD5AD; } .updateRow { font-weight: bold; color: red; } h3 { font-weight: normal; } p strong { font-weight: bold; } .hour { color: purple; } </style> </head> <body> <h3>Hi, anh Huy</h3>";
        protected string _middle = " <table id=\"customers\"> <tr> <th>STT</th> <th>Tên Game</th> <th>Cập Nhật</th> </tr>";
        protected string _footer = " </table> <h3>AnLNT</h3> </body> </html>";

        protected string ConverDayOfWeek(DayOfWeek dayOfWeek)
        {
            switch (dayOfWeek)
            {
                case DayOfWeek.Monday:
                    return "Thứ 2";
                case DayOfWeek.Tuesday:
                    return "Thứ 3";
                case DayOfWeek.Wednesday:
                    return "Thứ 4";
                case DayOfWeek.Thursday:
                    return "Thứ 5";
                case DayOfWeek.Friday:
                    return "Thứ 6";
                case DayOfWeek.Saturday:
                    return "Thứ 7";
                case DayOfWeek.Sunday:
                    return "Chủ Nhật";
            }
            return "";
        }
        public string Render(string xmlDataFile)
        {
            StringBuilder result = new StringBuilder();

            try
            {
                DateTime today = DateTime.Now;

                string hour = today.ToShortTimeString();
                string date = today.ToShortDateString();
                string dayOfWeek = ConverDayOfWeek(today.DayOfWeek);

                string timeParagraph = string.Format("<p>Kết quả <strong>{0}, {1} <span class=\"hour\">{2}</span></strong></p>", dayOfWeek, date, hour);

                result.Append(_header);
                result.Append(timeParagraph);
                result.Append(_middle);

                XmlDocument document = new XmlDocument();

                document.Load(xmlDataFile);

                XmlNodeList games = document.SelectNodes("//game");
                if (null == games || 0 == games.Count)
                {
                    return "";

                }

                int count = 1;

                foreach (XmlNode game in games)
                {
                    XmlAttribute id = game.Attributes["id"];
                    XmlAttribute value = game.Attributes["value"];
                    if (id != null && value != null)
                    {
                        string trClass = "";

                        if (count % 2 == 0)
                        {
                            trClass = "alt";
                        }

                        string update = "Không";
                        if ("1" == value.Value)
                        {
                            update = "<span class=\"updateRow\">CÓ</span>";
                        }

                        string row = string.Format("<tr class=\"{0}\"> <td>{1}</td> <td>{2}</td> <td>{3}</td> </tr>",
                            trClass, count, id.Value, update);
                        result.Append(row);

                        count++;
                    }
                }
            }
            catch (System.Exception ex)
            {
                Singleton.Instance.WriteLog(ex.ToString(), "ERROR");
                return "";
            }

            result.Append(_footer);
            return result.ToString();
           
        }

        public string RenderLogContent(String logFile)
        {
            StringBuilder builder = new StringBuilder();

            using (StreamReader reader = new StreamReader(new FileStream(logFile, FileMode.Open, FileAccess.Read, FileShare.ReadWrite), Encoding.Unicode))
            {
                string line;
                while ((line = reader.ReadLine()) != null)
                {
                    builder.AppendLine(line);
                }
            }
            return builder.ToString();
        }
    }
}
