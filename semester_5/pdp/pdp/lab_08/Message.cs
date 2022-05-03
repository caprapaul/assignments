using System;

namespace lab_08
{
    [Serializable]
    public struct Message
    {
        public int Tag { get; set; }
        public MessageData Payload { get; set; }
    }
}
