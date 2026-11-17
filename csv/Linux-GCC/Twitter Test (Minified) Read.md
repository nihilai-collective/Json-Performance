
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1960.28 | 0.0573091 | 6971.87ms | 264040 | 1280 | 6.93683e+06 | 128455 | 0.063963 | 2.5878 | 10.299 | 1.89341 | 0.00401642 | 0.000296093 | 2.997e-05 | 1(Win) | true |
| simdjson (ondemand) | 1705.9 | 0.0999631 | 7896.95ms | 264040 | 320 | 6.96724e+06 | 147610 | 0.177499 | 2.9671 | 10.7143 | 1.8331 | 0.00931264 | 6.93905e-05 | 1.85815e-05 | 2(Loss) | true |
