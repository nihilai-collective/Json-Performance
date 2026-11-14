
----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3217.43 | 2.50309 | 38.412ms | 905 | 4890 | 220466 | 268.25 | 3.99058 | 1(Win) | true |
| simdjson (reflection) | 2380.24 | 3.01539 | 46.7932ms | 905 | 2560 | 306042 | 362.6 | 1.79674 | 2(Loss) | true |
| Glaze | 635.362 | 3.03085 | 132.006ms | 905 | 160 | 271209 | 1358.4 | 0.831354 | 3(Loss) | true |
