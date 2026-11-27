
----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2289.02 | 0.305196 | 6446.21ms | 264040 | 30 | 3.38158e+06 | 110007 | 0.0430999 | 2.20874 | 8.13327 | 1.42647 | 0.00871926 | 2.08302e-05 | 1.28768e-05 | 1(Win) | true |
| simdjson (ondemand) | 2027.8 | 0.0685445 | 7469.52ms | 264040 | 1280 | 9.27356e+06 | 124178 | 0.0565902 | 2.50365 | 9.29185 | 1.51771 | 0.00825438 | 5.61912e-05 | 3.38609e-05 | 2(Loss) | true |
