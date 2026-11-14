
----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 5107.27 | 7.00575 | 89.7042ms | 3873 | 80 | 205360 | 723.2 | 0.877193 | 1(Win) | true |
| simdjson (reflection) | 3076.96 | 1.01388 | 130.251ms | 3873 | 2560 | 379194 | 1200.4 | 0.233801 | 2(Loss) | true |
| Glaze | 2100.53 | 1.96669 | 177.392ms | 3873 | 160 | 191350 | 1758.4 | 0.457038 | 3(Loss) | true |
