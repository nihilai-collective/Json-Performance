
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 293.651 | 0.0371861 | 9054.5ms | 1834197 | 80 | 3.92537e+08 | 5.95682e+06 | 0.47696 | 1(Win) | true |
| simdjson (ondemand) | 191.323 | 0.151557 | 6448.98ms | 1834197 | 40 | 7.68012e+09 | 9.14277e+06 | 0.469312 | 2(Loss) | true |
