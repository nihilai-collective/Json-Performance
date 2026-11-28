
----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2685.88 | 2.28466 | 53.7229ms | 1213 | 2560 | 247874 | 430.7 | 1.07947 | 1(Win) | true |
| simdjson (reflection) | 2406 | 2.92274 | 60.073ms | 1213 | 1280 | 252766 | 480.8 | 1.5561 | 2(Loss) | true |
| Glaze | 680.795 | 3.12831 | 155.173ms | 1213 | 80 | 226047 | 1699.2 | 2.90698 | 3(Loss) | true |
