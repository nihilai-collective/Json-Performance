
----
### Github Events Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1613.79 | 0.0495364 | 4499.99ms | 53331 | 1280 | 311979 | 31516.1 | 0.0535055 | 3.18012 | 11.4116 | 2.19187 | 0.00990417 | 4.87814e-05 | 3.42935e-05 | 1(Win) | true |
| simdjson (ondemand) | 1213.04 | 0.0409468 | 5581.89ms | 53331 | 2560 | 754556 | 41928.2 | 0.329352 | 4.21298 | 16.6139 | 2.98845 | 0.0154647 | 6.09402e-05 | 4.47822e-05 | 2(Loss) | true |
