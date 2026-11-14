
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 910.352 | 0.106914 | 7976.15ms | 2090234 | 80 | 4.3846e+08 | 2.1897e+06 | 0.0873196 | 5.57607 | 27.3243 | 5.06579 | 0.0218243 | 0.0790229 | 0.00012797 | 1(Win) | true |
| simdjson (ondemand) | 896.92 | 0.055193 | 8110.02ms | 2090234 | 160 | 2.40752e+08 | 2.2225e+06 | 0.0433242 | 5.63891 | 26.4284 | 4.36085 | 0.0218202 | 0.0804596 | 0.000155796 | 2(Loss) | true |
