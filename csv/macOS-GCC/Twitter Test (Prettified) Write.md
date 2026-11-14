
----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 17645.5 | 0.120844 | 4103.1ms | 716365 | 640 | 1.40096e+06 | 38716.8 | 0.084646 | 1(Win) | true |
| Glaze | 3513.68 | 0.385883 | 9595ms | 716365 | 640 | 3.60277e+08 | 194434 | 0.868574 | 2(Loss) | true |
| simdjson (reflection) | 419.817 | 0.11273 | 5062.67ms | 716365 | 160 | 5.38452e+08 | 1.62733e+06 | 0.803749 | 3(Loss) | true |
