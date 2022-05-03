using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace lab_04
{
    public class TaskParser : IParser
    {
        public TaskParser(List<string> urls)
        {
            Urls = urls;
        }

        public List<string> Urls { get; set; }
        
        public void Run()
        {
            Task[] tasks = Urls.Select((url, i) => Task.Run(() => Start(new Session(url, i)))).ToArray();
            Task.WaitAll(tasks);
        }
        
        private Task Start(Session session)
        {
            session.BeginConnectAsync().Wait();
            session.LogConnected();
            
            int numberOfBytes = session.BeginSendAsync().Result;
            session.LogSent(numberOfBytes);
            
            session.BeginReceiveAsync().Wait();
            session.LogReceived();
            
            session.ShutdownAndClose();
            return Task.CompletedTask;
        }
    }
}
