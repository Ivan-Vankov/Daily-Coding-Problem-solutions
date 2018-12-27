using System;
using System.Text;

// Daily Coding Problem #29
namespace Run_Lenght_Encoding {
	class RunLengthEncoding {
		public static string Encode(string msg) {
			if (msg.Length == 0) {
				return "";
			}
			int currNum = 0;
			char currChar = msg[0];
			StringBuilder encode = new StringBuilder(msg.Length);

			for (int i = 0; i < msg.Length; ++i) {
				if (msg[i] == currChar) {
					++currNum;
				}
				else {
					if (currNum == 1) {
						encode.Append(currChar);
					}
					else {
						encode.Append(currNum).Append(currChar);
					}
					currNum = 1;
				}
				currChar = msg[i];
			}
			if (currNum == 1) {
				encode.Append(currChar);
			}
			else {
				encode.Append(currNum).Append(currChar);
			}
			return encode.ToString();
		}

		public static string Decode(string code) {
			StringBuilder decode = new StringBuilder(code.Length);
			StringBuilder buff = new StringBuilder(code.Length);
			int cnt = 0;

			for (int i = 0; i < code.Length; ++i) {
				if (code[i] < '0' || code[i] > '9') {
					decode.Append(code[i]);
				}
				else {
					while (code[i] >= '0' && code[i] <= '9') {
						buff.Append(code[i++]);
					}
					cnt = Int32.Parse(buff.ToString());
					buff.Clear();
					for (int j = 0; j < cnt; ++j) {
						decode.Append(code[i]);
					}
				}
			}
			return decode.ToString();
		}
	}

	class Program {
		static void Main(string[] args) {
			string msg = "Haay budyy. How's it goiiiiin?";
			Console.WriteLine("Original message: {0}", msg);
			string buff = RunLengthEncoding.Encode(msg);
			Console.WriteLine("Encoded  message: {0}", buff);
			Console.WriteLine("Decoded  message: {0}", RunLengthEncoding.Decode(buff));
		}
	}
}
