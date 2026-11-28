
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3345.25 | 3.36625 | 37.335ms | 905 | 2560 | 193095 | 258 | 1.14943 | 1(Win) | true |
| simdjson (reflection) | 2579.42 | 2.87598 | 46.306ms | 905 | 2560 | 237063 | 334.6 | 0.416667 | 2(Loss) | true |
| Glaze | 864.458 | 1.42843 | 126.863ms | 905 | 30 | 6101.63 | 998.4 | 0 | 3(Loss) | true |
