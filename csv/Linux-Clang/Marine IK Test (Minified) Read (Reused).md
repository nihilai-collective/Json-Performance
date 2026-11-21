
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 970.712 | 0.213375 | 6417.21ms | 1834197 | 40 | 5.9137e+08 | 1.802e+06 | 0.0385095 | 2.55045 | 1(Win) | true |
| Jsonifier (two-stage) | 880.439 | 0.0483667 | 6878.49ms | 1834197 | 80 | 7.38716e+07 | 1.98677e+06 | 0.0259576 | 2.81197 | 2(Loss) | true |
| Glaze | 749.792 | 0.420646 | 8075.21ms | 1834197 | 80 | 7.7043e+09 | 2.33295e+06 | 0.727135 | 3.30196 | 3(Loss) | true |
| simdjson (ondemand) | 695.556 | 0.0739831 | 8497.26ms | 1834197 | 80 | 2.76939e+08 | 2.51486e+06 | 0.0401139 | 3.55942 | 4(Loss) | true |
