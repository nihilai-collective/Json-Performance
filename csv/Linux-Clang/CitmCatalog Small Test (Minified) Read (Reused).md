
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1985.47 | 0.152319 | 914.989ms | 3223 | 4890 | 27189.9 | 1548.09 | 0.103353 | 2.60669 | 10.3317 | 1.84642 | 0.00109051 | 5.58359e-05 | 1.21824e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1621.37 | 0.212726 | 947.483ms | 3223 | 1280 | 20816.6 | 1895.74 | 0.015003 | 3.18499 | 13.0773 | 2.18089 | 0.00108425 | 5.42972e-05 | 1.33319e-05 | 2(Loss) | true |
| Glaze | 1603.26 | 0.152286 | 952.385ms | 3223 | 40 | 340.951 | 1917.15 | 0.0182596 | 3.22381 | 13.4353 | 2.45206 | 0.00112473 | 0.000124108 | 6.2054e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1117.14 | 0.233937 | 1036.79ms | 3223 | 1280 | 53028.9 | 2751.39 | 0 | 4.59126 | 17.7017 | 2.73689 | 0.00157704 | 0.000106413 | 4.12077e-05 | 4(Loss) | true |
