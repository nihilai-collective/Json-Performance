
----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 853.181 | 0.144007 | 8357.3ms | 4506447 | 40 | 2.10482e+09 | 5.03725e+06 | 0.276418 | 5.94399 | 26.8781 | 5.42164 | 0.0130514 | 0.080836 | 0.0150133 | 1(Win) | true |
| simdjson (ondemand) | 499.833 | 0.126955 | 6390.02ms | 4506447 | 30 | 3.57468e+09 | 8.59824e+06 | 0.0123254 | 10.1483 | 43.7018 | 7.7793 | 0.0359104 | 0.0790057 | 0.0209321 | 2(Loss) | true |
