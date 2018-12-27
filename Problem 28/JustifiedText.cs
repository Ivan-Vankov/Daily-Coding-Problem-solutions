using System;
using System.Collections.Generic;
using System.Text;

// Daily Coding Problem #28
namespace Justified_Text {
    class JustifiedText {
		public static List<string> Justify(string[] list, int k) {
			List<string> justified = new List<string>();
			StringBuilder curr = new StringBuilder();
			int numOfWords = 0;
			int currWordsLen = 0;
			int i = 0;
			int j = 0;
			int spacesLeft = 0;
			while (i < list.Length) {
				if(currWordsLen + list[i].Length + numOfWords - 1 > k) {
					spacesLeft = k - currWordsLen - numOfWords + 1;
					for (; j < i - 1; ++j) {
						curr.Append(list[j]).Append(" ");
						if (numOfWords == 1) {
							for (int m = 0; m < spacesLeft; ++m) {
								curr.Append(" ");
							}
						}
						else {
							for (int m = 0; m < spacesLeft / (numOfWords - 1); ++m) {
								curr.Append(" ");
							}
							if(spacesLeft % (numOfWords - 1) != 0) {
								curr.Append(" ");
							}
							spacesLeft -= spacesLeft / (numOfWords - 1) + spacesLeft % (numOfWords - 1);
							--numOfWords;
						}
					}
					justified.Add(curr.Append(list[j++]).ToString());
					curr.Clear();
					numOfWords = 0;
					currWordsLen = 0;
				}
				else {
					++numOfWords;
					currWordsLen += list[i++].Length;
				}
			}

			spacesLeft = k - currWordsLen - numOfWords + 1;
			for (; j < i - 1; ++j) {
				curr.Append(list[j]).Append(" ");
				if (numOfWords == 1) {
					for (int m = 0; m < spacesLeft; ++m) {
						curr.Append(" ");
					}
				}
				else {
					for (int m = 0; m < spacesLeft / (numOfWords - 1); ++m) {
						curr.Append(" ");
					}
					if (spacesLeft % (numOfWords - 1) != 0) {
						curr.Append(" ");
					}
					spacesLeft -= spacesLeft / (numOfWords - 1) + spacesLeft % (numOfWords - 1);
					--numOfWords;
				}
			}
			justified.Add(curr.Append(list[j]).ToString());

			return justified;
		}

		static void Main(string[] args) {
			string[] list = { "the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog" };
			List<string> justified = Justify(list, 16);
			foreach (string i in justified) {
				Console.WriteLine(i);
			}
		}
    }
}
