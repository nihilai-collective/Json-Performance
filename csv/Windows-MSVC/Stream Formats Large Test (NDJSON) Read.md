
----
### Stream Formats Large Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 18026.5 | 0.122203 | 5471.08ms | 16197086 | 160 | 1.75443e+08 | 856892 | 1.79952 | 0.168556 | 1(Win) | true |
| simdjson (ondemand) | 14716.3 | 0.144489 | 6852.81ms | 16197086 | 80 | 1.84008e+08 | 1.04964e+06 | 0.0215504 | 0.20648 | 2(Loss) | true |
