
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2199.8 | 0.625829 | 5795.11ms | 7351818 | 30 | 1.19359e+10 | 3.18722e+06 | 1.04649 | 1.12537 | 1(Win) | true |
| Jsonifier | 2070.79 | 0.812687 | 5870.01ms | 7351818 | 30 | 2.27137e+10 | 3.38579e+06 | 1.04503 | 1.19549 | 2(Loss) | true |
| Glaze | 706.717 | 1.16326 | 7338.93ms | 7351818 | 40 | 5.32739e+11 | 9.92086e+06 | 1.46955 | 3.50316 | 3(Loss) | true |
| simdjson (ondemand) | 485.221 | 1.48571 | 10732.1ms | 7351818 | 40 | 1.84348e+12 | 1.44496e+07 | 1.27154 | 5.10233 | 4(Loss) | true |
