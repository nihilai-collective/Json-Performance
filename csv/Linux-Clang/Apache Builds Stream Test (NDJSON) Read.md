
----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1944.57 | 0.0593981 | 8248.07ms | 4212000 | 80 | 1.20438e+08 | 2.06569e+06 | 0.0438661 | 2.59825 | 11.4437 | 2.08965 | 0.0111175 | 0.0663689 | 0.00209831 | 1(Win) | true |
| simdjson (ondemand) | 1575.62 | 0.0952003 | 9743.07ms | 4212000 | 80 | 4.71239e+08 | 2.5494e+06 | 0.365258 | 3.234 | 13.512 | 2.36363 | 0.0100315 | 0.0662347 | 0.00196254 | 2(Loss) | true |
