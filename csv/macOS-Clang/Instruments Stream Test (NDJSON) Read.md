
----
### Instruments Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1346.06 | 0.0935824 | 9471.57ms | 4197496 | 30 | 2.3236e+08 | 2.97389e+06 | 1.26266 | 1(Win) | true |
| simdjson (ondemand) | 1104.12 | 0.1538 | 5582.91ms | 4197496 | 40 | 1.24372e+09 | 3.62555e+06 | 0.221035 | 2(Loss) | true |
