
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1722.28 | 0.150144 | 180.069ms | 3223 | 30 | 215.402 | 1784.67 | 0.169678 | 1.41388 | 1(Win) | true |
| Jsonifier (two-stage) | 1555.64 | 0.127302 | 207.013ms | 3223 | 30 | 189.799 | 1975.83 | 0.0253122 | 1.56956 | 2(Loss) | true |
| Glaze | 1348.27 | 0.120692 | 237.398ms | 3223 | 40 | 302.82 | 2279.72 | 0.617534 | 1.81506 | 3(Loss) | true |
| simdjson (ondemand) | 1015.31 | 0.216713 | 308.072ms | 3223 | 2560 | 110188 | 3027.35 | 0.152438 | 2.41563 | 4(Loss) | true |
