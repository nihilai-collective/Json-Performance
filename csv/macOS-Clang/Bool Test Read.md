
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 350.3 | 0.887566 | 343.615ms | 905 | 640 | 306054 | 2463.81 | 3.08724 | 1(Win) | true |
| simdjson (ondemand) | 246.449 | 0.931713 | 379.695ms | 905 | 320 | 340690 | 3502.05 | 0.302653 | 2(Loss) | true |
