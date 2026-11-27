
----
### Instruments Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13759.3 | 0.0494807 | 1572.83ms | 213963 | 40 | 2153.85 | 14830 | 0.0674764 | 0.179643 | 1(Win) | true |
| Glaze | 3694.23 | 0.5928 | 5566.45ms | 213963 | 80 | 8.57699e+06 | 55235 | 0.445536 | 0.669742 | 2(Loss) | true |
