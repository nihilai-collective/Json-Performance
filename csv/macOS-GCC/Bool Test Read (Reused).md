
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 228.535 | 0.315136 | 382.037ms | 905 | 4890 | 692620 | 3776.55 | 0.785933 | 1(Win) | true |
| simdjson (ondemand) | 153.054 | 0.326854 | 539.056ms | 905 | 4890 | 1.66121e+06 | 5639.02 | 1.88291 | 2(Loss) | true |
