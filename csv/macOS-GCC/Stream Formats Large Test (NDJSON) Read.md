
----
### Stream Formats Large Test (NDJSON) Read Results [(View the data used in the following test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 8421.26 | 0.612888 | 5692.45ms | 16197086 | 80 | 1.01105e+10 | 1.83426e+06 | 0.0693077 | 1(Win) | true |
| simdjson (ondemand) | 7231.75 | 0.806462 | 6298.56ms | 16197086 | 30 | 8.90177e+09 | 2.13596e+06 | 0.401089 | 2(Loss) | true |
