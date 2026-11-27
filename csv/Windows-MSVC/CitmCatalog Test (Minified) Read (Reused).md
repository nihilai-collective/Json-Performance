
----
### CitmCatalog Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1674.25 | 0.177205 | 8251.46ms | 500299 | 160 | 4.0803e+07 | 284976 | 0.445433 | 1.47858 | 1(Win) | true |
| Jsonifier (two-stage) | 1347.24 | 0.325742 | 5097.59ms | 500299 | 80 | 1.06466e+08 | 354149 | 0.248747 | 1.83748 | 2(Loss) | true |
| Glaze | 778.771 | 0.161913 | 8504.14ms | 500299 | 160 | 1.57444e+08 | 612661 | 0.166719 | 3.17898 | 3(Loss) | true |
| simdjson (ondemand) | 643.838 | 0.121179 | 10118.9ms | 500299 | 160 | 1.29026e+08 | 741060 | 0.327005 | 3.84521 | 4(Loss) | true |
