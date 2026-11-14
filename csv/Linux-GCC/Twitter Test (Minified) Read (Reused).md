
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2302.33 | 0.347401 | 6429.41ms | 264040 | 80 | 1.15493e+07 | 109371 | 0.0820499 | 2.199 | 8.9289 | 1.57967 | 0.00549486 | 2.16823e-05 | 5.20754e-06 | 1(Win) | true |
| simdjson (ondemand) | 1936.34 | 0.102503 | 7615.8ms | 264040 | 640 | 1.13717e+07 | 130043 | 0.232711 | 2.61151 | 9.33722 | 1.5185 | 0.0114237 | 5.36614e-05 | 3.50326e-05 | 2(Loss) | true |
