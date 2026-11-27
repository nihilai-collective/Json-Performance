
----
### Random Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1087.66 | 0.142608 | 7551.43ms | 676745 | 320 | 2.2914e+08 | 593379 | 0.145302 | 1(Win) | true |
| simdjson (ondemand) | 546.916 | 0.181294 | 7435.58ms | 676745 | 80 | 3.66156e+08 | 1.18006e+06 | 0.141612 | 2(Loss) | true |
