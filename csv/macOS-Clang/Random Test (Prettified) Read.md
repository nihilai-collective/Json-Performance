
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1490.18 | 0.361909 | 5352.46ms | 676745 | 640 | 1.57236e+09 | 433098 | 2.0421 | 1(Win) | true |
| simdjson (ondemand) | 1163.76 | 0.126335 | 7065.17ms | 676745 | 320 | 1.57079e+08 | 554577 | 0.802235 | 2(Loss) | true |
