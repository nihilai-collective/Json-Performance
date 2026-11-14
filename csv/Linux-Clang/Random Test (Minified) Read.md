
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1204.54 | 0.333333 | 8208.95ms | 409725 | 160 | 1.87076e+08 | 324392 | 0.415488 | 2.0551 | 1(Win) | true |
| simdjson (ondemand) | 1063.12 | 0.14389 | 9567.85ms | 409725 | 30 | 8.39088e+06 | 367546 | 0.0691456 | 2.32849 | 2(Loss) | true |
