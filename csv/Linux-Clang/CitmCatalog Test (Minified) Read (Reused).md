
----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2788.74 | 0.192078 | 5350.74ms | 500299 | 160 | 1.72791e+07 | 171089 | 0.588539 | 0.887627 | 1(Win) | true |
| Jsonifier (two-stage) | 2275.25 | 0.106896 | 6273.21ms | 500299 | 320 | 1.60794e+07 | 209701 | 0.0920807 | 1.08797 | 2(Loss) | true |
| Glaze | 1808.02 | 0.204694 | 7739.78ms | 500299 | 80 | 2.33429e+07 | 263892 | 0.4783 | 1.3692 | 3(Loss) | true |
| simdjson (ondemand) | 1188.4 | 0.1552 | 5519.72ms | 500299 | 80 | 3.10605e+07 | 401483 | 0.351836 | 2.08311 | 4(Loss) | true |
