using System;

// Daily Coding Problem #30
namespace Water_Filling {
	class WaterFilling {
		public static int FillWater(int[] towers) {
			if (towers.Length <= 1) {
				return 0;
			}
			int cnt = 0;
			int currMax = towers[0];
			for (int i = 1; i < towers.Length; ++i) {
				if (towers[i] > currMax) {
					currMax = towers[i];
				}
				else {
					cnt += currMax - towers[i];
				}
			}

			return cnt;
		}
	}

	class Program {
		static void Main(string[] args) {
			int[] arr = { 3, 0, 1, 3, 0, 5 };
			Console.WriteLine("Water filled: {0}", WaterFilling.FillWater(arr));
		}
	}
}
