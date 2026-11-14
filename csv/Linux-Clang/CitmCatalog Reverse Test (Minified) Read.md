
----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 686.707 | 0.0519391 | 8880.45ms | 500299 | 160 | 2.08365e+07 | 694798 | 0.0779223 | 7.37501 | 36.6865 | 7.57417 | 0.0223259 | 0.00858233 | 2.85329e-05 | 1(Win) | true |
| simdjson (ondemand) | 422.668 | 0.178939 | 7178.68ms | 500299 | 30 | 1.22403e+08 | 1.12884e+06 | 0.317391 | 12.0986 | 65.5821 | 13.0764 | 0.0328618 | 0.0125226 | 5.45007e-05 | 2(Loss) | true |
