
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 811.833 | 0.0693567 | 7901.93ms | 1834197 | 80 | 1.78659e+08 | 2.15466e+06 | 0.113498 | 1(Win) | true |
| Jsonifier (two-stage) | 643.747 | 0.253161 | 10397ms | 1834197 | 30 | 1.41963e+09 | 2.71726e+06 | 0.370224 | 2(Loss) | true |
| Glaze | 504.275 | 0.376336 | 6006.76ms | 1834197 | 80 | 1.36332e+10 | 3.4688e+06 | 0.124213 | 3(Loss) | true |
| simdjson (ondemand) | 380.932 | 0.612574 | 7368.04ms | 1834197 | 40 | 3.165e+10 | 4.59196e+06 | 1.14139 | 4(Loss) | true |
