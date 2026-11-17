
----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 646.662 | 0.0241515 | 9096.21ms | 56369 | 4890 | 1.97117e+06 | 83131 | 0.0431614 | 7.91236 | 35.0349 | 7.33999 | 0.0118357 | 4.42091e-05 | 2.89649e-05 | 1(Win) | true |
| simdjson (ondemand) | 209.208 | 0.032534 | 6731.3ms | 56369 | 1280 | 8.94561e+06 | 256959 | 0.22868 | 24.3746 | 132.868 | 28.2675 | 0.044731 | 3.4843e-05 | 1.43447e-05 | 2(Loss) | true |
