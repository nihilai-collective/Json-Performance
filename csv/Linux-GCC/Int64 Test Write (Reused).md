
----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2612.15 | 0.0566135 | 55.578ms | 1313 | 320 | 23.5681 | 479.366 | 0.00456353 | 0.898025 | 1(Win) | true |
| simdjson (reflection) | 2547.08 | 0.0919347 | 57.4627ms | 1313 | 80 | 16.3416 | 491.613 | 0.226809 | 0.917527 | 2(Loss) | true |
| Glaze | 1317.14 | 0.0586613 | 102.126ms | 1313 | 80 | 24.8804 | 950.675 | 0.023673 | 1.82738 | 3(Loss) | true |
