
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2880.38 | 0.199159 | 134.933ms | 3873 | 4890 | 31893.7 | 1282.32 | 0.187175 | 0.841545 | 1(Win) | true |
| simdjson (stage-1) | 1325.9 | 0.0552092 | 284.954ms | 3873 | 40 | 94.6147 | 2785.72 | 0.0679519 | 1.84913 | 2(Loss) | true |
