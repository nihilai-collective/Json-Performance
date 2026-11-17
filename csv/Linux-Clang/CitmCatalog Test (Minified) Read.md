
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1257.4 | 0.0431092 | 9898.7ms | 500299 | 640 | 1.71249e+07 | 379450 | 0.194799 | 4.02301 | 17.989 | 3.39912 | 0.0164763 | 0.0184542 | 5.24093e-05 | 1(Win) | true |
| simdjson (ondemand) | 1125.87 | 0.0999798 | 5523.71ms | 500299 | 160 | 2.8723e+07 | 423782 | 0.0244245 | 4.50599 | 18.6546 | 3.0036 | 0.0231247 | 0.0205571 | 2.72212e-05 | 2(Loss) | true |
