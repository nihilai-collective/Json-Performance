
----
### CitmCatalog Small Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1392.27 | 0.0334563 | 1437.48ms | 9739 | 1280 | 6375.94 | 6670.98 | 0.0397518 | 3.72033 | 16.2393 | 3.1993 | 0.00323771 | 4.2917e-05 | 2.4226e-05 | 1(Win) | true |
| simdjson (ondemand) | 886.782 | 0.055869 | 1815.98ms | 9739 | 30 | 1027.21 | 10473.6 | 0.0678353 | 5.83326 | 27.8069 | 5.53414 | 0.00860458 | 5.134e-05 | 1.0268e-05 | 2(Loss) | true |
