
----
### Instruments Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1810.63 | 0.0576015 | 6633.02ms | 108313 | 640 | 691112 | 57049.3 | 0.159099 | 2.82542 | 12.3934 | 2.48232 | 0.00340348 | 6.67914e-06 | 2.06289e-06 | 1(Win) | true |
| simdjson (ondemand) | 1633.72 | 0.0619411 | 7248.86ms | 108313 | 1280 | 1.96324e+06 | 63227.1 | 0.0376107 | 3.11054 | 14.4579 | 2.29223 | 0.00615963 | 1.00259e-05 | 3.72907e-06 | 2(Loss) | true |
