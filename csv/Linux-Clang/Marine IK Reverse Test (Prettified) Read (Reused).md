
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2761.95 | 0.35273 | 8659.13ms | 7351818 | 160 | 1.28281e+10 | 2.53851e+06 | 0.364473 | 1.82619 | 7.94452 | 1.43335 | 0.0097498 | 0.054217 | 0.000728301 | 1(Win) | true |
| Jsonifier | 2637.21 | 0.571862 | 9040.96ms | 7351818 | 40 | 9.24573e+09 | 2.65858e+06 | 0.168305 | 1.91477 | 8.81804 | 2.0339 | 0.0066163 | 0.0271687 | 0.000964704 | 2(Loss) | true |
| simdjson (ondemand) | 2318.1 | 0.112073 | 10170.6ms | 7351818 | 40 | 4.59609e+08 | 3.02457e+06 | 0.0905766 | 2.17705 | 9.45645 | 1.4366 | 0.00986644 | 0.053637 | 0.00136287 | 3(Loss) | true |
| Glaze | 2217.92 | 0.111785 | 5148.84ms | 7351818 | 40 | 4.99486e+08 | 3.16117e+06 | 0.915428 | 2.27072 | 10.2813 | 2.06793 | 0.00941035 | 0.0272544 | 0.00318922 | 4(Loss) | true |
