
----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1013.6 | 0.0656832 | 6104.25ms | 4197496 | 80 | 5.38323e+08 | 3.94932e+06 | 0.0727851 | 5.00113 | 27.5621 | 5.67743 | 0.000955856 | 0.0822121 | 0.00569998 | 1(Win) | true |
| simdjson (ondemand) | 750.999 | 0.112922 | 8175.03ms | 4197496 | 30 | 1.08688e+09 | 5.33029e+06 | 0.124672 | 6.74848 | 34.5093 | 5.39404 | 0.0142429 | 0.0823158 | 0.00221947 | 2(Loss) | true |
