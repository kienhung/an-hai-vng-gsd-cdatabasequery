using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Mail;
using System.IO;
using System.Xml;

namespace MailHelper
{
    
    public class MailConfig
    {
        private MailAddress _from;
        public MailAddress From
        {
            get { return _from; }
            set { _from = value; }
        }

        private MailAddress _to;
        public MailAddress To
        {
            get { return _to; }
            set { _to = value; }
        }

        private MailAddress _logReceive;

        public MailAddress LogReceive
        {
            get { return _logReceive; }
            set { _logReceive = value; }
        }

        private List<MailAddress> _cc;

        public List<MailAddress> CC
        {
            get { return _cc; }
            set { _cc = value; }
        }
        private string _password;

        public string Password
        {
            get { return _password; }
            set { _password = value; }
        }
        public static MailConfig Load(string fileName)
        {
            
            try
            {
                MailConfig mailConfig = new MailConfig();

                XmlDocument document = new XmlDocument();
                document.Load(fileName);

                XmlNode mailNode = document.SelectSingleNode("//mail");

                XmlAttribute onAttribute = mailNode.Attributes["on"];
                if (null == onAttribute || onAttribute.Value != "1")
                {
                    Singleton.Instance.WriteLog("Turn off sending email", "WARN");
                    return null;
                }
                XmlNode fromNode = document.SelectSingleNode("//from");

                XmlAttribute usernameAttribute = fromNode.Attributes["username"];
                XmlAttribute passwordAttribute = fromNode.Attributes["password"];

                mailConfig.From = new MailAddress(usernameAttribute.Value);
                mailConfig.Password = passwordAttribute.Value;

                XmlNode directToNode = mailNode.SelectSingleNode("./to");
                usernameAttribute = directToNode.Attributes["username"];
                mailConfig.To = new MailAddress(usernameAttribute.Value);

                XmlNode logReceiveNode = mailNode.SelectSingleNode("./log");
                if (logReceiveNode != null)
                {
                    usernameAttribute = logReceiveNode.Attributes["username"];
                    if (usernameAttribute != null)
                    {
                        mailConfig.LogReceive = new MailAddress(usernameAttribute.Value);
                    }
                }

                XmlNodeList ccNodeList = mailNode.SelectNodes("./cc/to");
                if (ccNodeList != null)
                {
                    mailConfig.CC = new List<MailAddress>();
                    foreach (XmlNode toNode in ccNodeList)
                    {
                        usernameAttribute = toNode.Attributes["username"];
                        if (usernameAttribute != null)
                        {
                            mailConfig.CC.Add(new MailAddress(usernameAttribute.Value));
                        }
                    }
                }


                return mailConfig;
            }
            catch (System.Exception ex)
            {
                Singleton.Instance.WriteLog(ex.ToString(), "ERROR");
                return null;
            }
        }
    }
}
