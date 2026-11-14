
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1157.59 | 0.0303811 | 1147.23ms | 5092 | 4890 | 7942.99 | 4195.02 | 0.19604 | 4.42712 | 18.4292 | 3.50823 | 0.00333793 | 6.81931e-05 | 2.68274e-05 | 1(Win) | true |
| simdjson (ondemand) | 1133.26 | 0.0418142 | 1158.86ms | 5092 | 1280 | 4109.35 | 4285.07 | 0.0904207 | 4.51789 | 18.3979 | 3.07994 | 0.00275325 | 3.57485e-05 | 8.59191e-06 | 2(Loss) | true |
