
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1351.6 | 0.149434 | 7554.84ms | 409725 | 160 | 2.9861e+07 | 289097 | 0.0332698 | 3.75086 | 18.0091 | 3.50411 | 0.00891154 | 0.0195382 | 8.36537e-05 | 1(Win) | true |
| simdjson (ondemand) | 981.11 | 0.121819 | 5166.88ms | 409725 | 80 | 1.88309e+07 | 398268 | 0.163623 | 5.17438 | 19.945 | 3.78726 | 0.0166993 | 0.0430577 | 4.44505e-05 | 2(Loss) | true |
