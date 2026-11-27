
----
### Canada Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5692.19 | 0.057141 | 252.792ms | 14795 | 30 | 60.1851 | 2478.77 | 0.0671926 | 0.430132 | 1(Win) | true |
| Glaze | 3429.47 | 0.0773605 | 418.695ms | 14795 | 40 | 405.204 | 4114.23 | 0.0419453 | 0.717254 | 2(Loss) | true |
| simdjson (reflection) | 486.683 | 0.199983 | 2951.47ms | 14795 | 640 | 2.15131e+06 | 28991.4 | 0.981593 | 5.08245 | 3(Loss) | true |
