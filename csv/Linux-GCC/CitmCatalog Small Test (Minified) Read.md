
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1179.98 | 0.0306873 | 1131.26ms | 5092 | 4890 | 7799.22 | 4115.4 | 0.0590199 | 4.40419 | 17.7056 | 3.35324 | 0.00293945 | 8.06831e-05 | 2.96789e-05 | 1(Win) | true |
| simdjson (ondemand) | 1162.97 | 0.0265878 | 1139.21ms | 5092 | 4890 | 6027.18 | 4175.61 | 0.00698492 | 4.46981 | 17.9038 | 3.08896 | 0.00279021 | 5.84742e-05 | 1.93174e-05 | 2(Loss) | true |
