
----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1789.64 | 0.108235 | 318.513ms | 5839 | 80 | 907.341 | 3111.53 | 0.0353649 | 1(Win) | true |
| Jsonifier (two-stage) | 1641.82 | 0.12623 | 347.107ms | 5839 | 30 | 549.885 | 3391.67 | 0.0442065 | 2(Loss) | true |
| Glaze | 1288.3 | 0.0743404 | 460.528ms | 5839 | 4890 | 50489.7 | 4322.37 | 0.949655 | 3(Loss) | true |
| simdjson (ondemand) | 1195.65 | 0.113587 | 471.578ms | 5839 | 80 | 2238.79 | 4657.29 | 0.0889183 | 4(Loss) | true |
