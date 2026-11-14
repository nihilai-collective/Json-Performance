
----
### CitmCatalog Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 524.501 | 0.956868 | 6027.4ms | 4525120 | 40 | 2.47931e+11 | 8.2278e+06 | 3.16315 | 1(Win) | true |
| simdjson (ondemand) | 406.298 | 0.586755 | 8070.83ms | 4525120 | 40 | 1.55362e+11 | 1.06215e+07 | 4.63366 | 2(Loss) | true |
