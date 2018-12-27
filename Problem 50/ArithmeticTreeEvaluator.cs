using System;
using System.Collections.Generic;

namespace Arithmetic_Tree_Evaluator {
	class ArithmeticTreeEvaluator {
		class Node {
			public Node Left { get; set; }
			public Node Right { get; set; }
			public string Value { get; set; }

			public Node(string value, Node left = null, Node right = null) {
				Value = value;
				Left = left;
				Right = right;
			}
		}

		class ArithmeticTree {
			private static readonly Dictionary<string, Func<int, int, int>> Operations =
				new Dictionary<string, Func<int, int, int>>() {
					{"*", (x,y) => x * y },
					{"+", (x,y) => x + y },
					{"-", (x,y) => x - y },
					{"/", (x,y) => y == 0?
								   throw new DivideByZeroException("Dividing by zero in ArithmeticTree"):
								   x / y }
				};

			private readonly Node root;

			public ArithmeticTree(Node root) {
				this.root = root;
			}

			public int EvalTree() {
				if (root == null) {
					throw new ArgumentNullException("Null root in arithmetic tree");
				}
				return EvalTreeHelper(root);
			}

			private int EvalTreeHelper(Node curr) {
				if (Int32.TryParse(curr.Value, out int res)) { return res; }
				else {
					int leftVal = EvalTreeHelper(curr.Left);
					int rightVal = EvalTreeHelper(curr.Right);

					if (Operations.ContainsKey(curr.Value)) {
						return Operations[curr.Value](leftVal, rightVal);
					}
					else { throw new ArgumentException("Unknown operator in ArithmeticTree"); }
				}
			}
		}

		static void Main(string[] args) {
			Node root = new Node("*",
							new Node("+",
								new Node("3"),
								new Node("2")),
							new Node("+",
								new Node("4"),
								new Node("5")));
			ArithmeticTree arTree = new ArithmeticTree(root);
			try {
				Console.WriteLine(arTree.EvalTree());
			}
			catch (Exception ex) {
				Console.WriteLine(ex.Message);
			}
		}
	}
}