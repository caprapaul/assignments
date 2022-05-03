using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace lab_04
{
    public class Session
    {
        private const int DefaultHttpPort = 80;
        private const int BufferSize = 1024;
        private static readonly Regex ContentLengthRegex = new(@"Content-Length: ([0-9]+)");

        public Session(string url, int id)
        {
            int pathDelimiterIndex = url.IndexOf('/');
            string baseUrl = pathDelimiterIndex < 0 ? url : url[..pathDelimiterIndex];
            string urlPath = pathDelimiterIndex < 0 ? "/" : url[pathDelimiterIndex..];

            IPHostEntry ipHostInformation = Dns.GetHostEntry(baseUrl);
            IPAddress ipAddress = ipHostInformation.AddressList[0];
            
            Id = id;
            BaseUrl = baseUrl;
            UrlPath = urlPath;
            EndPoint = new IPEndPoint(ipAddress, DefaultHttpPort);
            Connection = new Socket(ipAddress.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
        }

        public int Id { get; }

        public string BaseUrl { get; }

        public string UrlPath { get; }

        public IPEndPoint EndPoint { get; }
        public Socket Connection { get; set; }

        public StringBuilder ResponseContent { get; } = new();

        private int GetResponseContentLength()
        {
            string value = ContentLengthRegex
                .Match(ResponseContent.ToString())
                .Groups[1].Value;
            return string.IsNullOrEmpty(value) ? -1 : int.Parse(value);
        }

        private bool IsContentFullyReceived => ResponseContent.ToString().Contains("\r\n\r\n");

        public void BeginConnect(Action<Session> onConnected)
        {
            Connection.BeginConnect(EndPoint, asyncResult =>
            {
                Connection.EndConnect(asyncResult);
                onConnected(this);
            }, null);
        }

        public void BeginSend(Action<Session, int> onSent)
        {
            var stringToSend = $"GET {UrlPath} HTTP/1.1\r\nHost: {BaseUrl}\r\nContent-Length: 0\r\n\r\n";
            byte[] encodedString = Encoding.ASCII.GetBytes(stringToSend);

            Connection.BeginSend(encodedString, 0, encodedString.Length, SocketFlags.None, asyncResult =>
            {
                int numberOfSentBytes = Connection.EndSend(asyncResult);
                onSent(this, numberOfSentBytes);
            }, null);
        }

        public void BeginReceive(Action<Session> onReceived)
        {
            var buffer = new byte[BufferSize];
            ResponseContent.Clear();

            Connection.BeginReceive(buffer, 0, BufferSize, SocketFlags.None, asyncResult =>
                HandleReceiveResult(asyncResult, buffer, onReceived), null);
        }

        public Task BeginConnectAsync()
        {
            return Task.Run(() =>
            {
                var promise = new TaskCompletionSource();

                BeginConnect(_ => promise.TrySetResult());

                return promise.Task;
            });
        }

        public Task<int> BeginSendAsync()
        {
            return Task.Run(() =>
            {
                var promise = new TaskCompletionSource<int>();

                BeginSend((_, numberOfSentBytes) =>
                    promise.TrySetResult(numberOfSentBytes));

                return promise.Task;
            });
        }

        public Task BeginReceiveAsync()
        {
            return Task.Run(() =>
            {
                var taskCompletion = new TaskCompletionSource();

                BeginReceive(_ => taskCompletion.TrySetResult());

                return taskCompletion.Task;
            });
        }

        public void ShutdownAndClose()
        {
            Connection.Shutdown(SocketShutdown.Both);
            Connection.Close();
        }

        private void HandleReceiveResult(
            IAsyncResult asyncResult,
            byte[] buffer,
            Action<Session> onReceived)
        {
            int numberOfReadBytes = Connection.EndReceive(asyncResult);
            ResponseContent.Append(Encoding.ASCII.GetString(buffer, 0, numberOfReadBytes));

            if (!IsContentFullyReceived)
            {
                Connection.BeginReceive(buffer, 0, BufferSize, SocketFlags.None, asyncResult =>
                    HandleReceiveResult(asyncResult, buffer, onReceived), null);
                return;
            }

            onReceived(this);
        }
        
        public void LogConnected()
        {
            Console.WriteLine($"{Id}: Connected to {BaseUrl}{UrlPath}");
        }

        public void LogSent(int numberOfSentBytes)
        {
            Console.WriteLine($"{Id}: Sent {numberOfSentBytes} bytes");
        }

        public void LogReceived()
        {
            Console.WriteLine($"{Id}: Content length: {GetResponseContentLength()}");
        }
    }
}
