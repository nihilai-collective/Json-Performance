
----
### Instruments Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1277.66 | 0.155011 | 10073.5ms | 4197496 | 80 | 1.88697e+09 | 3.1331e+06 | 0.24727 | 1(Win) | true |
| simdjson (ondemand) | 1174.1 | 0.185734 | 5271.52ms | 4197496 | 80 | 3.20806e+09 | 3.40945e+06 | 0.0123876 | 2(Loss) | true |
