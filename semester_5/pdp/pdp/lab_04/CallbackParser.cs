using System.Collections.Generic;
using System.Threading;

namespace lab_04
{
    public class CallbackParser : IParser
    {
        public CallbackParser(List<string> urls)
        {
            Urls = urls;
        }

        public List<string> Urls { get; set; }
        
        public void Run()
        {
            for (var i = 0; i < Urls.Count; i++)
            {
                Start(new Session(Urls[i], i));
            }
        }
        
        private void Start(Session session)
        {
            session.BeginConnect(OnConnected);
            
            do
            {
                Thread.Sleep(100);
            }
            while (session.Connection.Connected);
        }

        private void OnConnected(Session session)
        {
            session.LogConnected();
            session.BeginSend(OnSent);
        }

        private void OnSent(Session session, int numberOfSentBytes)
        {
            session.LogSent(numberOfSentBytes);
            session.BeginReceive(OnReceived);
        }

        private void OnReceived(Session session)
        {
            session.LogReceived();
            session.ShutdownAndClose();
        }
    }
}
