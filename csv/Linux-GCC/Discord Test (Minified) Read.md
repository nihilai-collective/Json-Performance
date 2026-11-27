
----
### Discord Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1551.45 | 0.082076 | 3493.97ms | 56369 | 1280 | 1.03526e+06 | 34650 | 0.12946 | 1.59461 | 1(Win) | true |
| simdjson (ondemand) | 1476.34 | 0.180377 | 3673.97ms | 56369 | 320 | 1.38046e+06 | 36412.8 | 0.0847454 | 1.6758 | 2(Loss) | true |
