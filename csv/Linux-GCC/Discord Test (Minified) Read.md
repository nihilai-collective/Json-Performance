
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1458.51 | 0.0694267 | 4435.92ms | 56369 | 160 | 104769 | 36857.8 | 0.000237398 | 3.53231 | 15.0925 | 2.97584 | 0.00783354 | 2.86061e-05 | 2.00687e-05 | 1(Win) | true |
| simdjson (ondemand) | 1285.45 | 0.0167645 | 4908.36ms | 56369 | 4890 | 240357 | 41820 | 0.00715148 | 3.99212 | 15.7675 | 2.79637 | 0.0102245 | 1.68623e-05 | 8.4892e-06 | 2(Loss) | true |
