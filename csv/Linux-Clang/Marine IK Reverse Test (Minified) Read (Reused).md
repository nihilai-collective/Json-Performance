
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 407.861 | 0.229549 | 6776.36ms | 1834197 | 30 | 2.90763e+09 | 4.28878e+06 | 0.0334948 | 12.395 | 61.2039 | 12.7205 | 0.0376136 | 0.322776 | 0.0155594 | 1(Win) | true |
| simdjson (ondemand) | 277.478 | 0.140962 | 9828.98ms | 1834197 | 40 | 3.15865e+09 | 6.30402e+06 | 0.257337 | 18.3464 | 102.346 | 20.5133 | 0.0482184 | 0.767718 | 0.00550464 | 2(Loss) | true |
