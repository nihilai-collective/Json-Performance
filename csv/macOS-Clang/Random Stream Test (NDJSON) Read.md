
----
### Random Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1163.66 | 0.301088 | 6055.84ms | 4506447 | 80 | 9.89218e+09 | 3.69324e+06 | 0.706377 | 1(Win) | true |
| simdjson (ondemand) | 776.809 | 0.25311 | 8914.05ms | 4506447 | 80 | 1.56873e+10 | 5.53248e+06 | 0.347768 | 2(Loss) | true |
