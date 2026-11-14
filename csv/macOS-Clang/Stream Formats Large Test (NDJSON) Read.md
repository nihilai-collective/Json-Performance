
----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 8729.85 | 0.0813854 | 5532.11ms | 16197086 | 40 | 8.29495e+07 | 1.76942e+06 | 0.412424 | 1(Win) | true |
| Jsonifier (generic) | 8122.3 | 0.0633485 | 5965.7ms | 16197086 | 80 | 1.16112e+08 | 1.90177e+06 | 0.0164025 | 2(Loss) | true |
