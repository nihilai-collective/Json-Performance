
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 970.765 | 1.18792 | 7911.19ms | 4506447 | 80 | 2.2126e+11 | 4.42711e+06 | 0.272811 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 603.705 | 1.18425 | 5773.83ms | 4506447 | 30 | 2.13221e+11 | 7.11885e+06 | 5.71674 | -(Loss) | false |
