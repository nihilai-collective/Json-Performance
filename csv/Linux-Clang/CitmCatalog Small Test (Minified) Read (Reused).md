
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2036.43 | 0.17605 | 906.881ms | 3223 | 2560 | 18075.6 | 1509.35 | 0.175673 | 2.55717 | 10.3317 | 1.84642 | 0.00115151 | 5.18733e-05 | 3.51478e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1620.21 | 0.119931 | 953.426ms | 3223 | 4890 | 25313.3 | 1897.1 | 0.273681 | 3.18861 | 13.0773 | 2.18089 | 0.00111583 | 6.22443e-05 | 1.02154e-05 | 2(Loss) | true |
| Glaze | 1595.57 | 0.130504 | 952.364ms | 3223 | 4890 | 30906.2 | 1926.39 | 0.126171 | 3.23741 | 13.4353 | 2.45206 | 0.00126665 | 5.07599e-05 | 7.55054e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1119.25 | 0.116738 | 1039.56ms | 3223 | 4890 | 50257.5 | 2746.2 | 0.0114574 | 4.58512 | 17.7062 | 2.73999 | 0.00207862 | 6.54803e-05 | 1.29438e-05 | 4(Loss) | true |
