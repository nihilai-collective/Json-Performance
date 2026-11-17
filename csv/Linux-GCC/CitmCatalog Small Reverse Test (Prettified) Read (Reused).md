
----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1316.44 | 0.0730088 | 1490.77ms | 9739 | 320 | 8490.37 | 7055.26 | 0.000177173 | 3.93383 | 16.5143 | 3.28468 | 0.00407607 | 4.58851e-05 | 5.77575e-06 | 1(Win) | true |
| simdjson (ondemand) | 885.659 | 0.0380992 | 1817.17ms | 9739 | 1280 | 20433.2 | 10486.9 | 0.0390662 | 5.83405 | 27.8232 | 5.51818 | 0.0092586 | 2.96809e-05 | 8.10209e-06 | 2(Loss) | true |
