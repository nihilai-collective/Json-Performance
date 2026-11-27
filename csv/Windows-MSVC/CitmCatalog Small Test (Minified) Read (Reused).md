
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1141.71 | 0.155224 | 344.421ms | 3223 | 2560 | 44706.4 | 2692.19 | 0.505269 | 2.63922 | 1(Win) | true |
| Jsonifier (two-stage) | 902.729 | 0.140228 | 417.551ms | 3223 | 4890 | 111477 | 3404.89 | 0.240205 | 3.34555 | 2(Loss) | true |
| Glaze | 816.657 | 0.184536 | 451.413ms | 3223 | 80 | 3859.18 | 3763.75 | 0.500668 | 3.70096 | 3(Loss) | true |
| simdjson (ondemand) | 689.652 | 0.156553 | 516.45ms | 3223 | 640 | 31157.7 | 4456.88 | 0.258759 | 4.38693 | 4(Loss) | true |
