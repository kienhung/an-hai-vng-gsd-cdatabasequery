using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Mail;
using System.IO;
using System.Xml;
using System.Net.Mime;
using System.Threading;

namespace MailHelper
{
    class Program
    {
        public static string GetLogFilePath(string xmlDataFile)
        {
  
            try
            {
                XmlDocument document = new XmlDocument();

                document.Load(xmlDataFile);
                XmlNode log = document.SelectSingleNode("//log");
                if (null == log)
                {
                    throw new Exception("Unable to load log node");
                }
                XmlAttribute path = log.Attributes["path"];
                if (null == path)
                {
                    throw new Exception("Unable to get path attribute");
                }

                return path.Value;
            }
            catch (System.Exception ex)
            {
                Singleton.Instance.WriteLog(ex.ToString(), "ERROR");
            }
            return "";
        }
        static int Main(string[] args)
        {

            string appDirectory = AppDomain.CurrentDomain.BaseDirectory;

            try
            {

                string mailConfigPath = string.Format(@"{0}config.xml", appDirectory);

                MailConfig mailConfig = MailConfig.Load(mailConfigPath);
                if (mailConfig == null)
                {
                    Singleton.Instance.WriteLog("mailConfig is null", "WARN");
                    return 0;
                }

                MailMessage message = new MailMessage(mailConfig.From, mailConfig.To);
                if (mailConfig.CC != null && mailConfig.CC.Count > 0)
                {
                    foreach (MailAddress address in mailConfig.CC)
                    {
                        message.CC.Add(address);
                    }
                }

                message.Subject = "Kết quả tool kiểm tra cập nhật game";
                message.BodyEncoding = Encoding.UTF8;
                message.IsBodyHtml = true;

                BodyRender bodyRender = new BodyRender();

                string dataFile = string.Format(@"{0}data.xml", appDirectory);
                message.Body = bodyRender.Render(dataFile);

                if ("" == message.Body)
                {
                    Singleton.Instance.WriteLog("message.Body empty", "ERROR");
                    return 1;
                }

                SmtpClient client = new SmtpClient("smtp.gmail.com", 587);

                client.UseDefaultCredentials = false;
                client.EnableSsl = true;
                client.Credentials = new NetworkCredential(message.From.Address, mailConfig.Password);

                client.Send(message);

                //send log

                string logFile = GetLogFilePath(dataFile);
                if (logFile.Equals("") == false)
                {
                    String strLogBody = bodyRender.RenderLogContent(logFile);

                    MailMessage logMessage = new MailMessage(mailConfig.From, mailConfig.LogReceive);
                    logMessage.Subject = "Tool Log";
                    logMessage.Body = strLogBody;

                    client.Send(logMessage);

                    //MailMessage logMessage = new MailMessage(mailConfig.From, mailConfig.LogReceive);
                    //logMessage.Subject = "Tool Log";
                    //logMessage.Body = "FYI";

                    //Attachment data = new Attachment(logFile, MediaTypeNames.Application.Octet);
                    //ContentDisposition disposition = data.ContentDisposition;

                    //disposition.CreationDate = System.IO.File.GetCreationTime(logFile);
                    //disposition.ModificationDate = System.IO.File.GetLastWriteTime(logFile);
                    //disposition.ReadDate = System.IO.File.GetLastAccessTime(logFile);

                    //logMessage.Attachments.Add(data);
                    //client.Send(logMessage);
                }
            }

            catch (System.Exception ex)
            {
                Singleton.Instance.WriteLog(ex.ToString(), "ERROR");
            }
            
            return 0;
        }
    }
}
