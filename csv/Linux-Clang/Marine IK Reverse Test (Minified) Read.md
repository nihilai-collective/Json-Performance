
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 847.645 | 0.377442 | 6513.89ms | 1834197 | 80 | 4.85349e+09 | 2.06363e+06 | 0.389698 | 2.92075 | 1(Win) | true |
| Jsonifier (two-stage) | 779.781 | 0.81408 | 7095.51ms | 1834197 | 80 | 2.66791e+10 | 2.24323e+06 | 1.06403 | 3.17495 | 2(Loss) | true |
| Glaze | 693.518 | 0.0904209 | 7886.18ms | 1834197 | 30 | 1.5604e+08 | 2.52225e+06 | 0.183367 | 3.56987 | 3(Loss) | true |
| simdjson (ondemand) | 549.026 | 0.183126 | 9944.42ms | 1834197 | 30 | 1.02124e+09 | 3.18605e+06 | 1.06052 | 4.5089 | 4(Loss) | true |
