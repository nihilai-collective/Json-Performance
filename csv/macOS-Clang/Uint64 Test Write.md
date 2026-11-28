
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1021.62 | 0.515267 | 125.178ms | 1213 | 320 | 10893.3 | 1132.33 | 1.93534 | 1(Win) | true |
| Glaze | 162.026 | 0.120998 | 804.111ms | 1213 | 40 | 2985.16 | 7139.65 | 0.261001 | 2(Loss) | true |
