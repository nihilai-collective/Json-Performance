
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 471.969 | 0.124163 | 929.327ms | 4604 | 640 | 85390.2 | 9302.97 | 0.0790022 | 6.4237 | 1(Win) | true |
| Jsonifier (two-stage) | 435.877 | 0.101667 | 1012.96ms | 4604 | 1280 | 134250 | 10073.3 | 0.110009 | 6.95426 | 2(Loss) | true |
| simdjson (ondemand) | 260.463 | 0.0387503 | 1691.81ms | 4604 | 4890 | 208660 | 16857.4 | 0.088905 | 11.6479 | 3(Loss) | true |
| Glaze | 255.933 | 0.0499358 | 1716.99ms | 4604 | 4890 | 358880 | 17155.7 | 0.12279 | 11.8576 | 4(Loss) | true |
