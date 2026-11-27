
----
### Apache Builds Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19086.8 | 0.289786 | 477.894ms | 94653 | 1280 | 240419 | 4729.35 | 0.364861 | 0.129003 | 1(Win) | true |
| Glaze | 5586.3 | 0.0841249 | 1620.27ms | 94653 | 4890 | 903605 | 16158.8 | 0.114989 | 0.442491 | 2(Loss) | true |
