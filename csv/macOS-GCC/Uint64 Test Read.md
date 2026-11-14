
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2592.35 | 1.02525 | 141.768ms | 3873 | 1280 | 273134 | 1424.8 | 2.29753 | 1(Win) | true |
| simdjson (stage-1) | 1378.2 | 1.40942 | 308.423ms | 3873 | 160 | 228281 | 2680 | 0.179426 | 2(Loss) | true |
