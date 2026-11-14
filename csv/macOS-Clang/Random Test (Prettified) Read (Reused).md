
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1734.26 | 0.405491 | 5143.5ms | 676745 | 80 | 1.82168e+08 | 372144 | 1.02423 | 1(Win) | true |
| simdjson (ondemand) | 1267.22 | 0.309243 | 6953.24ms | 676745 | 30 | 7.44159e+07 | 509298 | 0.412356 | 2(Loss) | true |
