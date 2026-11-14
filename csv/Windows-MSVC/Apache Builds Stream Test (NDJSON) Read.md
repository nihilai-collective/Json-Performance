
----
### Apache Builds Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 998.241 | 0.350982 | 7682.73ms | 4212000 | 30 | 5.98408e+09 | 4.02395e+06 | 1.01171 | 2.4801 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 955.174 | 0.96691 | 7927.58ms | 4212000 | 30 | 4.96027e+10 | 4.20539e+06 | 2.74549 | 2.59181 | -(Loss) | false |
