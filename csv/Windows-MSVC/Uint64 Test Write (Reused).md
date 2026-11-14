
----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4491.71 | 0.113801 | 96.5236ms | 3873 | 4890 | 4282.24 | 822.311 | 1.27565 | 0.65715 | 1(Win) | true |
| Glaze | 1554.78 | 0.165855 | 266.226ms | 3873 | 160 | 2483.88 | 2375.62 | 0.183824 | 1.93765 | 2(Loss) | true |
