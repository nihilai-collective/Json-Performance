
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 702.095 | 1.09463 | 546.385ms | 3873 | 80 | 265296 | 5260.8 | 1.20192 | 1(Win) | true |
| simdjson (ondemand) | 461.451 | 0.262636 | 967.495ms | 3873 | 30 | 13257.9 | 8004.27 | 0 | 2(Loss) | true |
