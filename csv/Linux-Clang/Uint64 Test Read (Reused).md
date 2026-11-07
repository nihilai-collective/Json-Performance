
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3292.78 | 0.0244753 | 116.041ms | 3873 | 320 | 24.1199 | 1121.72 | 0.0136528 | 0.734323 | 1(Win) | true |
| Glaze | 1500.57 | 0.0420583 | 249.867ms | 3873 | 40 | 42.8692 | 2461.45 | 0.151223 | 1.63311 | 2(Loss) | true |
| Jsonifier (two-stage) | 909.826 | 0.116508 | 409.272ms | 3873 | 4890 | 109395 | 4059.66 | 0.0625009 | 2.70349 | 3(Loss) | true |
| simdjson (ondemand) | 664.628 | 0.0524012 | 562.182ms | 3873 | 80 | 678.437 | 5557.36 | 0.112815 | 3.70789 | 4(Loss) | true |
