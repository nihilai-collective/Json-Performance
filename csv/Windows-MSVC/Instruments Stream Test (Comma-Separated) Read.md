
----
### Instruments Stream Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1045.42 | 0.970732 | 5934.87ms | 4197495 | 40 | 5.5266e+10 | 3.82913e+06 | 0.048969 | 2.90718 | 1(Win) | true |
| simdjson (ondemand) | 780.365 | 0.776663 | 7938.93ms | 4197495 | 40 | 6.34908e+10 | 5.12971e+06 | 0.159734 | 3.89475 | 2(Loss) | true |
