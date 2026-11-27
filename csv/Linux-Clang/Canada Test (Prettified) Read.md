
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1807.59 | 0.0817472 | 8568.69ms | 5212421 | 80 | 4.04311e+08 | 2.75005e+06 | 0.160388 | 2.80922 | 13.6503 | 2.60269 | 0.0102021 | 0.0609387 | 0.00111435 | 1(Win) | true |
| simdjson (ondemand) | 1771.34 | 0.0576479 | 8761.04ms | 5212421 | 160 | 4.18758e+08 | 2.80632e+06 | 0.124775 | 2.85492 | 13.4607 | 2.2997 | 0.0103363 | 0.0618001 | 0.00372215 | 2(Loss) | true |
