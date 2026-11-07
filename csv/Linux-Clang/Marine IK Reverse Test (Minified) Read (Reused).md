
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 975.857 | 0.089618 | 6283.57ms | 1834197 | 30 | 7.74162e+07 | 1.7925e+06 | 0.202551 | 2.537 | 1(Win) | true |
| Jsonifier (two-stage) | 866.852 | 0.225145 | 7522.69ms | 1834197 | 30 | 6.19225e+08 | 2.01791e+06 | 0.772309 | 2.85604 | 2(Loss) | true |
| Glaze | 749.349 | 0.0373743 | 7997ms | 1834197 | 40 | 3.0446e+07 | 2.33433e+06 | 0.000603318 | 3.3039 | 3(Loss) | true |
| simdjson (ondemand) | 690.704 | 0.0504622 | 8621.95ms | 1834197 | 30 | 4.89961e+07 | 2.53253e+06 | 0.00328383 | 3.58443 | 4(Loss) | true |
