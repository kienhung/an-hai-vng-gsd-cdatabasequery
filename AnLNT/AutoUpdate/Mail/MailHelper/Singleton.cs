using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace MailHelper
{
    public sealed class Singleton
    {
        private static Singleton instance = null;
        private static readonly object padlock = new object();

        private string _logFilePath = "";

        Singleton()
        {
        }

        public static Singleton Instance
        {
            get
            {
                lock (padlock)
                {
                    if (instance == null)
                    {
                        instance = new Singleton();

                        DateTime now = DateTime.Now;

                        string appDirectory = AppDomain.CurrentDomain.BaseDirectory;
                        instance._logFilePath = string.Format("{0}log\\MailHelper {1}-{2}-{3} {4}-{5}-{6}.log", 
                                               appDirectory, now.Year, now.Month, now.Day, now.Hour, now.Minute, now.Second);

                    }
                    return instance;
                }
            }
        }
        public void WriteLog(string message, string type)
        {
            try
            { 
                StreamWriter writer = new StreamWriter(new FileStream(_logFilePath, FileMode.Append));

                type = string.Format("[{0}]", type);

                string output = string.Format("{0,-25}{1, -15}{2}", DateTime.Now, type, message);
                writer.WriteLine(output);
                writer.Close();
            }
            catch (System.Exception ex)
            {
                Console.Write(ex.ToString());
            }
        }
    }
}
