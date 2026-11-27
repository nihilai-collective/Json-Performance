
----
### Twitter Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16618.1 | 0.460908 | 4147.67ms | 716365 | 160 | 5.74457e+06 | 41110.6 | 0.0394214 | 0.148869 | 1(Win) | true |
| Glaze | 4261.32 | 0.135515 | 8171.86ms | 716365 | 2560 | 1.20835e+08 | 160321 | 0.131732 | 0.580853 | 2(Loss) | true |
| simdjson (reflection) | 571.87 | 0.2624 | 7484.32ms | 716365 | 30 | 2.94797e+08 | 1.19464e+06 | 1.16535 | 4.32919 | 3(Loss) | true |
