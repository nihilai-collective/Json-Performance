
----
### Random Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1722.98 | 0.152544 | 561.273ms | 8051 | 1280 | 59147.8 | 4456.25 | 0.408562 | 1.75746 | 1(Win) | true |
| Jsonifier (two-stage) | 1533.83 | 0.11808 | 611.758ms | 8051 | 1280 | 44720.3 | 5005.78 | 2.10536 | 1.97492 | 2(Loss) | true |
| Glaze | 1275.95 | 0.252023 | 728.632ms | 8051 | 160 | 36798.7 | 6017.5 | 0.501044 | 2.37461 | 3(Loss) | true |
| simdjson (ondemand) | 1093.35 | 0.15705 | 856.59ms | 8051 | 40 | 4865.38 | 7022.5 | 0.801435 | 2.77261 | 4(Loss) | true |
