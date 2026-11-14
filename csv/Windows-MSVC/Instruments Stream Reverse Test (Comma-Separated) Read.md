
----
### Instruments Stream Reverse Test (Comma-Separated) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 698.86 | 0.145151 | 8850.28ms | 4197495 | 80 | 5.53008e+09 | 5.72796e+06 | 0.535981 | 4.34872 | 1(Win) | true |
| simdjson (ondemand) | 493.732 | 0.139024 | 5828.76ms | 4197495 | 30 | 3.8115e+09 | 8.10772e+06 | 0.403412 | 6.15574 | 2(Loss) | true |
