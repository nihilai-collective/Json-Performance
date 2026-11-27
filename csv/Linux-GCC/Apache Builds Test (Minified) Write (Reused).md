
----
### Apache Builds Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21344.3 | 0.0682561 | 431.32ms | 94653 | 40 | 333.31 | 4229.15 | 0.0681312 | 0.115224 | 1(Win) | true |
| simdjson (reflection) | 14220.6 | 0.130256 | 633.948ms | 94653 | 4890 | 334302 | 6347.72 | 0.492637 | 0.173353 | 2(Loss) | true |
| Glaze | 6480.38 | 0.11661 | 1398.93ms | 94653 | 4890 | 1.29017e+06 | 13929.5 | 0.586138 | 0.381274 | 3(Loss) | true |
