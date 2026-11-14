
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 638.815 | 0.0290883 | 1502.92ms | 4604 | 2560 | 10232.8 | 6873.22 | 0.0317285 | 8.10926 | 32.5699 | 6.50912 | 0.00923501 | 4.55616e-05 | 9.24807e-06 | 1(Win) | true |
| simdjson (ondemand) | 620.523 | 0.018579 | 1516.94ms | 4604 | 4890 | 8451.05 | 7075.83 | 0.050132 | 8.34904 | 34.0367 | 5.96655 | 0.0104493 | 6.07634e-05 | 1.80336e-05 | 2(Loss) | true |
