
----
### CitmCatalog Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1523.47 | 0.071778 | 9249.46ms | 1151920 | 160 | 4.28628e+07 | 721089 | 0.0341866 | 3.32434 | 16.019 | 3.22027 | 0.0096591 | 0.0370448 | 6.96392e-05 | 1(Win) | true |
| simdjson (ondemand) | 925.642 | 0.2515 | 7556.82ms | 1151920 | 30 | 2.67272e+08 | 1.1868e+06 | 0.308124 | 5.50007 | 28.3063 | 5.71958 | 0.0153684 | 0.0897812 | 0.000714315 | 2(Loss) | true |
