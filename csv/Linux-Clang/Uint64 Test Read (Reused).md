
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 734.073 | 0.0521519 | 159.855ms | 1213 | 80 | 54.0348 | 1575.88 | 0.0190334 | 3.31977 | 1(Win) | true |
| simdjson (ondemand) | 321.807 | 0.127161 | 370.662ms | 1213 | 40 | 835.794 | 3594.72 | 0.288054 | 7.64122 | 2(Loss) | true |
