
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1841.58 | 0.0292098 | 3985.88ms | 56369 | 2560 | 186123 | 29191.1 | 0.113098 | 2.79198 | 12.9595 | 2.51 | 0.00528348 | 8.92556e-06 | 1.61464e-06 | 1(Win) | true |
| simdjson (ondemand) | 1505.89 | 0.026935 | 4690.93ms | 56369 | 2560 | 236683 | 35698.2 | 0.294642 | 3.39673 | 13.634 | 2.32712 | 0.010385 | 1.42476e-05 | 5.13497e-06 | 2(Loss) | true |
