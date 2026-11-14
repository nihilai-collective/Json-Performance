
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 572.895 | 0.15856 | 658.308ms | 3873 | 4890 | 511022 | 6447.22 | 0.0544388 | 4.30338 | 1(Win) | true |
| simdjson (ondemand) | 321.53 | 0.146819 | 1221.99ms | 3873 | 40 | 11378.2 | 11487.5 | 0.26913 | 7.67896 | 2(Loss) | true |
