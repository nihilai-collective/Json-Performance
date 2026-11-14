
----
### Apache Builds Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1442.97 | 0.0591662 | 8988.48ms | 124597 | 640 | 1.51924e+06 | 82347.3 | 0.176447 | 3.54343 | 16.2022 | 3.25295 | 0.00787631 | 1.32051e-05 | 7.98825e-06 | 1(Win) | true |
| simdjson (ondemand) | 926.276 | 0.0485127 | 6959.27ms | 124597 | 640 | 2.47871e+06 | 128282 | 0.010665 | 5.52841 | 25.9892 | 5.32316 | 0.0102698 | 7.51172e-06 | 1.98139e-06 | 2(Loss) | true |
