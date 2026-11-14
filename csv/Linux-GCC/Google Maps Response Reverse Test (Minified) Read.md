
----
### Google Maps Response Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 776.311 | 0.0345545 | 2177.61ms | 11812 | 2560 | 64361.5 | 14510.7 | 0.0155115 | 6.64124 | 29.5444 | 6.02439 | 0.0150056 | 3.95519e-05 | 1.55761e-05 | 1(Win) | true |
| simdjson (ondemand) | 701.343 | 0.034517 | 2331.39ms | 11812 | 640 | 19671.2 | 16061.8 | 0.0203275 | 7.34594 | 31.7569 | 6.21656 | 0.0133716 | 1.6006e-05 | 1.58737e-06 | 2(Loss) | true |
