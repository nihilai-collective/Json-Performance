
----
### CitmCatalog Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1264.59 | 0.0430264 | 9810.24ms | 500299 | 1280 | 3.37318e+07 | 377294 | 0.0143903 | 4.01954 | 17.9917 | 3.40013 | 0.0168521 | 0.0079828 | 2.32908e-05 | 1(Win) | true |
| simdjson (ondemand) | 1145.26 | 0.0898979 | 5395.32ms | 500299 | 160 | 2.24426e+07 | 416608 | 0.173909 | 4.43031 | 18.6464 | 3.00038 | 0.0211184 | 0.0115708 | 1.54907e-05 | 2(Loss) | true |
