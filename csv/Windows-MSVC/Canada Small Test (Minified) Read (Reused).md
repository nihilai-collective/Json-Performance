
----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 732.613 | 0.126558 | 766.094ms | 4630 | 2560 | 148946 | 6027.07 | 0.406721 | 4.12894 | 1(Win) | true |
| Jsonifier (two-stage) | 666.084 | 0.60518 | 826.724ms | 4630 | 2560 | 4.12016e+06 | 6629.06 | 0.00942907 | 4.54976 | 2(Loss) | true |
| simdjson (ondemand) | 365.121 | 0.35275 | 1382.35ms | 4630 | 2560 | 4.65868e+06 | 12093.3 | 0.689045 | 8.30865 | 3(Loss) | true |
| Glaze | 356.319 | 0.201261 | 1397.65ms | 4630 | 1280 | 796184 | 12392 | 0.164904 | 8.51608 | 4(Loss) | true |
