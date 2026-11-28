
----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 2653.48 | 1.52022 | 62.6742ms | 1313 | 4890 | 251662 | 471.899 | 0.632013 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2630.62 | 2.08452 | 55.2369ms | 1313 | 2560 | 252038 | 476 | 2.32158 | 1(Tie) | true |
| Glaze | 854.377 | 2.01897 | 145.516ms | 1313 | 320 | 280182 | 1465.6 | 0.659341 | 3(Loss) | true |
