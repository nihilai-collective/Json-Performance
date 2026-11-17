
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 623.529 | 0.521914 | 8871.34ms | 1834197 | 40 | 8.57504e+09 | 2.80537e+06 | 4.08848 | 1(Win) | true |
| Jsonifier (two-stage) | 538.25 | 0.212668 | 10311.7ms | 1834197 | 30 | 1.43301e+09 | 3.24984e+06 | 0.380906 | 2(Loss) | true |
| Glaze | 425.463 | 0.902668 | 6112.58ms | 1834197 | 40 | 5.50914e+10 | 4.11135e+06 | 1.16859 | 3(Loss) | true |
| simdjson (ondemand) | 390.479 | 0.298822 | 7024.11ms | 1834197 | 40 | 7.16775e+09 | 4.47969e+06 | 0.163114 | 4(Loss) | true |
