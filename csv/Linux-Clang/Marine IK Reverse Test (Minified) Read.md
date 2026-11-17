
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 780.592 | 0.105755 | 6947.78ms | 1834197 | 40 | 2.2465e+08 | 2.2409e+06 | 0.704008 | 3.17166 | 1(Win) | true |
| Jsonifier (two-stage) | 714.813 | 0.125553 | 7613.98ms | 1834197 | 40 | 3.77592e+08 | 2.44711e+06 | 0.951564 | 3.46354 | 2(Loss) | true |
| Glaze | 631.172 | 0.203523 | 8577.29ms | 1834197 | 30 | 9.54427e+08 | 2.77139e+06 | 0.141987 | 3.92245 | 3(Loss) | true |
| simdjson (ondemand) | 573.192 | 0.196562 | 9544.08ms | 1834197 | 40 | 1.4393e+09 | 3.05173e+06 | 0.313157 | 4.31923 | 4(Loss) | true |
