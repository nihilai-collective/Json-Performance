
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2624.08 | 0.0528087 | 8314.44ms | 7351818 | 160 | 3.18541e+08 | 2.67188e+06 | 0.0705665 | 1.91502 | 8.25799 | 1.535 | 0.0105262 | 0.0611643 | 0.000817912 | 1(Win) | true |
| Jsonifier | 2574.87 | 0.0470043 | 8493.41ms | 7351818 | 160 | 2.62104e+08 | 2.72295e+06 | 0.214024 | 1.95566 | 8.73357 | 1.99994 | 0.00751357 | 0.0342788 | 0.000425166 | 2(Loss) | true |
| simdjson (reflection) | 2264.47 | 0.0521155 | 9633.23ms | 7351818 | 40 | 1.04148e+08 | 3.0962e+06 | 0.110246 | 2.22883 | 9.70637 | 1.65689 | 0.00913207 | 0.0584193 | 0.000163245 | 3(Loss) | true |
| Glaze | 2064.82 | 0.0671593 | 5104.93ms | 7351818 | 80 | 4.16033e+08 | 3.39557e+06 | 0.0682708 | 2.44156 | 11.2406 | 2.23967 | 0.00901098 | 0.0335089 | 0.00049848 | 4(Loss) | true |
| simdjson (ondemand) | 1962.74 | 0.0832013 | 5377.06ms | 7351818 | 30 | 2.64999e+08 | 3.57216e+06 | 0.0281589 | 2.56825 | 10.5051 | 1.87229 | 0.0102592 | 0.0615029 | 0.000344473 | 5(Loss) | true |
