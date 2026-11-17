
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1555.82 | 0.0291641 | 1013.78ms | 4669 | 2560 | 1783.48 | 2861.97 | 0.051075 | 3.35422 | 13.9163 | 2.8006 | 0.00219659 | 3.5055e-05 | 2.09159e-06 | 1(Win) | true |
| simdjson (ondemand) | 1504.09 | 0.16023 | 1024.51ms | 4669 | 30 | 675.007 | 2960.4 | 0.0461436 | 3.47315 | 15.6682 | 2.30478 | 0.00122082 | 3.56964e-05 | 0 | 2(Loss) | true |
