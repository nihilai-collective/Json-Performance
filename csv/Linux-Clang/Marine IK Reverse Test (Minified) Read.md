
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 385.506 | 0.0981449 | 7057.94ms | 1834197 | 30 | 5.94959e+08 | 4.53748e+06 | 0.149467 | 6.4221 | 1(Win) | true |
| simdjson (ondemand) | 212.648 | 0.15784 | 5756.31ms | 1834197 | 40 | 6.74312e+09 | 8.22591e+06 | 0.270277 | 11.6424 | 2(Loss) | true |
