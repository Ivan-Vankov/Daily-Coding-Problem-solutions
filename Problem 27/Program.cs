using System;
using System.Collections.Generic;

// Daily Coding Problem #27

namespace Balanced_Mixed_Braces {
	class BalancedMixedBraces {
		public static bool BalanceCheck(string braces) {
			Stack<int> openBraces = new Stack<int>();
			int curlyCnt = 0;
			int roundCnt = 0;
			int sqrCnt = 0;
			for (int j = 0; j < braces.Length; ++j) {
				switch (braces[j]) {
					case ('{'): ++curlyCnt; openBraces.Push(j); break;
					case ('('): ++roundCnt; openBraces.Push(j); break;
					case ('['): ++sqrCnt; openBraces.Push(j); break;
					case ('}'):
						if (braces[openBraces.Peek()] != '{') { return false; }
						--curlyCnt; openBraces.Pop(); break;
					case (')'):
						if (braces[openBraces.Peek()] != '(') { return false; }
						--roundCnt; openBraces.Pop(); break;
					case (']'):
						if (braces[openBraces.Peek()] != '[') { return false; }
						--sqrCnt; openBraces.Pop(); break;
				}
				if (curlyCnt < 0 || sqrCnt < 0 || roundCnt < 0) {
					return false;
				}
			}
			if (curlyCnt != 0 || roundCnt != 0 || sqrCnt != 0) {
				return false;
			}
			return true;
		}
	}

    class Program {
        static void Main(string[] args) {
			string braces = "([{}{}])[]({})";

			Console.Write(braces);
			if (BalancedMixedBraces.BalanceCheck(braces)) {
				Console.WriteLine(" is balanced.");
			}
			else {
				Console.WriteLine(" isn't balanced.");
			}
        }
    }
}
