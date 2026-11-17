
----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 691.314 | 0.212244 | 8967.98ms | 500299 | 30 | 6.43728e+07 | 690168 | 0.202819 | 7.37737 | 35.6971 | 7.46767 | 0.0207511 | 0.0118689 | 5.3568e-05 | 1(Win) | true |
| simdjson (ondemand) | 423.858 | 0.267007 | 7163.35ms | 500299 | 320 | 2.89079e+09 | 1.12567e+06 | 0.198203 | 12.033 | 63.4992 | 13.0632 | 0.0359795 | 0.0191071 | 0.000335175 | 2(Loss) | true |
