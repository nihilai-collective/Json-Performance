
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 612.357 | 0.114025 | 9000.24ms | 1834197 | 40 | 4.2437e+08 | 2.85655e+06 | 0.346036 | 4.04295 | 1(Win) | true |
| simdjson (ondemand) | 580.781 | 0.244675 | 9197.25ms | 1834197 | 30 | 1.62917e+09 | 3.01185e+06 | 0.409892 | 4.26276 | 2(Loss) | true |
