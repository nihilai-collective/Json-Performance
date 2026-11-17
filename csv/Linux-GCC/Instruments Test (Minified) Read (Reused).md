
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1746 | 0.217533 | 6778ms | 108313 | 40 | 662496 | 59161.2 | 0.0899273 | 2.8944 | 13.1868 | 2.63173 | 0.00333178 | 1.54644e-05 | 1.24639e-05 | 1(Win) | true |
| simdjson (ondemand) | 1598.46 | 0.141095 | 7408.56ms | 108313 | 160 | 1.33015e+06 | 64621.8 | 0.0728323 | 3.20495 | 14.6005 | 2.34905 | 0.00542179 | 5.36639e-06 | 2.48123e-06 | 2(Loss) | true |
