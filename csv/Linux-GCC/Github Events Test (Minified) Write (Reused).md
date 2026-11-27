
----
### Github Events Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13248.5 | 0.0891052 | 432.439ms | 58581 | 80 | 1129.48 | 4216.88 | 0.0243012 | 0.185636 | 1(Win) | true |
| simdjson (reflection) | 10797.3 | 0.0265337 | 526.736ms | 58581 | 160 | 301.579 | 5174.19 | 0.132815 | 0.228061 | 2(Loss) | true |
| Glaze | 7579.79 | 0.205892 | 732.023ms | 58581 | 2560 | 589549 | 7370.55 | 0.812501 | 0.325396 | 3(Loss) | true |
