
----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1428.68 | 0.0357678 | 9878.75ms | 1151920 | 640 | 4.84107e+07 | 768934 | 0.0506839 | 3.58176 | 17.0623 | 3.3874 | 0.00973766 | 0.0398615 | 3.25774e-05 | 1(Win) | true |
| simdjson (ondemand) | 928.351 | 0.146611 | 7483.14ms | 1151920 | 40 | 1.20396e+08 | 1.18334e+06 | 0.189807 | 5.47753 | 29.1282 | 5.70489 | 0.0140457 | 0.0918568 | 1.30434e-05 | 2(Loss) | true |
