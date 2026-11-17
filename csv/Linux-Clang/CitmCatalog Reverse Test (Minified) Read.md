
----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 696.158 | 0.180134 | 8924.07ms | 500299 | 30 | 4.57255e+07 | 685365 | 0.0440057 | 7.34177 | 36.6901 | 7.5749 | 0.0220754 | 0.0226535 | 9.33442e-05 | 1(Win) | true |
| simdjson (ondemand) | 414.218 | 0.0777065 | 7340.92ms | 500299 | 30 | 2.40346e+07 | 1.15186e+06 | 0.035177 | 12.2024 | 65.6047 | 13.0831 | 0.0363365 | 0.0330706 | 6.86256e-05 | 2(Loss) | true |
