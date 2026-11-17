
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2165.36 | 0.112971 | 7051.82ms | 264040 | 160 | 2.76145e+06 | 116289 | 0.0204058 | 2.33857 | 8.95821 | 1.63349 | 0.00729359 | 4.05715e-05 | 3.25235e-05 | 1(Win) | true |
| simdjson (ondemand) | 1783.25 | 0.276816 | 8416.88ms | 264040 | 30 | 4.58372e+06 | 141207 | 0.0765192 | 2.83727 | 9.86512 | 1.52286 | 0.0140727 | 6.96864e-05 | 3.76206e-05 | 2(Loss) | true |
