
----
### Canada Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1790.51 | 0.0700989 | 250.763ms | 4630 | 30 | 89.6506 | 2466.07 | 0.0391834 | 1.36772 | 1(Win) | true |
| Glaze | 1413.1 | 0.121671 | 317.668ms | 4630 | 40 | 578.164 | 3124.7 | 0.254309 | 1.73741 | 2(Loss) | true |
| simdjson (reflection) | 1303.54 | 0.040328 | 371.846ms | 4630 | 80 | 149.285 | 3387.32 | 0.0435637 | 1.88449 | 3(Loss) | true |
