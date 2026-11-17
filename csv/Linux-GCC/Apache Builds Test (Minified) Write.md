
----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20277.6 | 0.0239901 | 1182.94ms | 94653 | 4890 | 5577.11 | 4451.62 | 0.0764583 | 0.251048 | 1.20076 | 0.18066 | 3.00398e-05 | 3.92565e-06 | 1.57933e-06 | 1(Win) | true |
| simdjson (reflection) | 13408 | 0.0383926 | 1410.59ms | 94653 | 2560 | 17103.3 | 6732.43 | 0.039894 | 0.379776 | 2.045 | 0.302885 | 6.4091e-05 | 2.60821e-06 | 7.55226e-07 | 2(Loss) | true |
| Glaze | 7823.91 | 0.0312294 | 1901.4ms | 94653 | 4890 | 63483.1 | 11537.5 | 0.0563955 | 0.643762 | 3.47139 | 0.569279 | 6.95404e-05 | 5.60221e-06 | 2.97287e-06 | 3(Loss) | true |
