
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 648.425 | 0.0908783 | 132.394ms | 905 | 30 | 43.8954 | 1331.03 | 0.125373 | 3.74232 | 1(Win) | true |
| simdjson (ondemand) | 460.115 | 0.510281 | 191.285ms | 905 | 160 | 14659 | 1875.78 | 0.0623462 | 5.30741 | 2(Loss) | true |
