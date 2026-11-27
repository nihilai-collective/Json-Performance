
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 515.078 | 0.276888 | 249.284ms | 1213 | 2560 | 98997.5 | 2245.89 | 0.540194 | 1(Win) | true |
| simdjson (ondemand) | 238.451 | 2.17334 | 484.385ms | 1213 | 30 | 333502 | 4851.33 | 0.489536 | 2(Loss) | true |
