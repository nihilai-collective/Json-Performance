
----
### CitmCatalog Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1453.65 | 0.0385168 | 9742.86ms | 1151920 | 640 | 5.42255e+07 | 755722 | 0.115352 | 3.49817 | 17.0618 | 3.38721 | 0.00936624 | 0.0398866 | 2.89924e-05 | 1(Win) | true |
| simdjson (ondemand) | 920.4 | 0.171728 | 7624.74ms | 1151920 | 30 | 1.26037e+08 | 1.19356e+06 | 0.336716 | 5.52163 | 29.1359 | 5.70734 | 0.0154171 | 0.0800947 | 9.71711e-05 | 2(Loss) | true |
