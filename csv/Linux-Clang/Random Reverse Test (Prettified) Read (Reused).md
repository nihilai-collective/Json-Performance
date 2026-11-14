
----
### Random Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1346 | 0.0362595 | 6738.95ms | 676745 | 160 | 4.83638e+06 | 479489 | 0.243904 | 3.75825 | 16.7587 | 3.31104 | 0.00781141 | 0.0168861 | 9.01373e-06 | 1(Win) | true |
| simdjson (ondemand) | 791.482 | 0.178827 | 5472.9ms | 676745 | 80 | 1.70108e+08 | 815425 | 0.0627714 | 6.42857 | 29.1334 | 5.20714 | 0.0203264 | 0.0263743 | 4.02847e-05 | 2(Loss) | true |
