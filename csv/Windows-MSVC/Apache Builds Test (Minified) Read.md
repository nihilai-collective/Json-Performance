
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 911.163 | 0.291829 | 5057.5ms | 94653 | 2560 | 2.13981e+08 | 99069.2 | 0.312506 | 3.33464 | 1(Win) | true |
| Glaze | 856.643 | 0.360561 | 5385.28ms | 94653 | 2560 | 3.69545e+08 | 105374 | 0.229844 | 3.547 | 2(Loss) | true |
| Jsonifier (two-stage) | 842.046 | 0.322488 | 5502.33ms | 94653 | 2560 | 3.05959e+08 | 107201 | 0.386462 | 3.60846 | 3(Loss) | true |
| simdjson (ondemand) | 726.372 | 0.263455 | 6361.87ms | 94653 | 2560 | 2.74411e+08 | 124273 | 0.197821 | 4.18326 | 4(Loss) | true |
