
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1046.36 | 0.130701 | 366.198ms | 3223 | 160 | 2358.49 | 2937.5 | 0.42735 | 2.34341 | 1(Win) | true |
| Jsonifier (two-stage) | 863.035 | 0.256832 | 428.213ms | 3223 | 4890 | 409139 | 3561.49 | 0.195851 | 2.84464 | 2(Loss) | true |
| Glaze | 575.239 | 0.172212 | 603.264ms | 3223 | 30 | 2540.23 | 5343.33 | 0.124611 | 4.28573 | 3(Loss) | true |
| simdjson (ondemand) | 516.587 | 0.175625 | 694.353ms | 3223 | 30 | 3275.86 | 5950 | 0.501672 | 4.78561 | 4(Loss) | true |
