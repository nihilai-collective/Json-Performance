
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1801.59 | 0.139991 | 4070.35ms | 56369 | 30 | 52346.5 | 29838.9 | 0.0120633 | 2.86175 | 13.2873 | 2.60734 | 0.00533922 | 1.36009e-05 | 8.27878e-06 | 1(Win) | true |
| simdjson (ondemand) | 1435.75 | 0.0289285 | 4832.59ms | 56369 | 2560 | 300342 | 37442.3 | 0.113488 | 3.56979 | 14.7335 | 2.35618 | 0.0120577 | 1.09352e-05 | 4.26182e-06 | 2(Loss) | true |
