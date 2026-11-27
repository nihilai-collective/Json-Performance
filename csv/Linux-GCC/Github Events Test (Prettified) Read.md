
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1526.83 | 0.0326269 | 4822.01ms | 65103 | 2560 | 450623 | 40664 | 0.182229 | 3.3317 | 11.6034 | 2.21568 | 0.0104468 | 5.12469e-05 | 3.08166e-05 | 1(Win) | true |
| simdjson (ondemand) | 1246.24 | 0.068174 | 5744.13ms | 65103 | 640 | 738271 | 49819.4 | 0.0647255 | 4.09463 | 14.7462 | 2.85737 | 0.0169069 | 6.95772e-05 | 4.48328e-05 | 2(Loss) | true |
