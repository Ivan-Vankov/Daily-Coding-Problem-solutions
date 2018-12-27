using System;

// Daily Coding Problem #32
namespace Exchange_Rate_Arbitrage {
	class Arbitrage {
		public static bool CheckForArbitrage(float[,] exchangeRates) {
			float eps = 0.01f;
			int n = exchangeRates.GetUpperBound(0);
			for (int i = 0; i < n - 1; ++i) {
				for (int j = i + 1; j < n; ++j) {
					float res = exchangeRates[i, j] - 1 / exchangeRates[j, i];
					if (res > eps || res < -eps) {
						return true;
					}
				}

			}
			return false;
		}
	}

	class Program {
		static void Main(string[] args) {
			// bgn
			// dollar
			// euro
			// pound
			float[,] exchangeRates = {
				{ 1f    , 0.59f , 0.51f , 0.46f },
				{ 1.69f , 1f    , 0.86f , 0.77f },
				{ 1.96f , 1.16f , 1f    , 0.89f },
				{ 2.20f , 1.30f , 1.12f , 1f    }
			};
			Console.WriteLine("Check if there is arbitrage: {0}",
				Arbitrage.CheckForArbitrage(exchangeRates));
		}
	}
}
