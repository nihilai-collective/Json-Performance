
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 876.814 | 0.125715 | 433.539ms | 3873 | 40 | 1121.79 | 4212.5 | 1.11502 | 3.43258 | 1(Win) | true |
| simdjson (ondemand) | 611.52 | 0.173818 | 623.525ms | 3873 | 160 | 17635.2 | 6040 | 0.248963 | 4.95136 | 2(Loss) | true |
