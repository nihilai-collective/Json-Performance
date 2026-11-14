
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3196.14 | 0.0399563 | 1825.97ms | 56369 | 30 | 1354.94 | 16819.6 | 0.0653573 | 1(Win) | true |
| Glaze | 1899.65 | 0.245194 | 2998.36ms | 56369 | 30 | 144435 | 28298.7 | 0.156535 | 2(Loss) | true |
| Jsonifier (two-stage) | 1680.14 | 0.0332344 | 3883.73ms | 56369 | 30 | 3392.23 | 31995.9 | 0.035121 | 3(Loss) | true |
| simdjson (ondemand) | 830.906 | 0.0578598 | 6664.54ms | 56369 | 4890 | 6.85235e+06 | 64697.7 | 0.0518831 | 4(Loss) | true |
