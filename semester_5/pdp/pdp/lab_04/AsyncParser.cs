using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace lab_04
{
    public class AsyncParser : IParser
    {
        public AsyncParser(List<string> urls)
        {
            Urls = urls;
        }

        public List<string> Urls { get; set; }
        
        public void Run()
        {
            Task[] tasks = Urls.Select((url, i) => Task.Run(() => Start(new Session(url, i)))).ToArray();
            Task.WaitAll(tasks);
        }
        
        private async Task Start(Session session)
        {
            await session.BeginConnectAsync();
            session.LogConnected();
            
            int numberOfBytes = await session.BeginSendAsync();
            session.LogSent(numberOfBytes);
            
            await session.BeginReceiveAsync();
            session.LogReceived();
            
            session.ShutdownAndClose();
        }
    }
}
