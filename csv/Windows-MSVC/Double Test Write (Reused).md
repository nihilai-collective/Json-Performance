
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 731.089 | 0.0745709 | 271.777ms | 1997 | 160 | 603.774 | 2605 | 0.0479616 | 3.35244 | 1(Win) | true |
| Glaze | 391.224 | 0.210167 | 470.961ms | 1798 | 2560 | 217219 | 4382.93 | 0.2303 | 6.28409 | 2(Loss) | true |
