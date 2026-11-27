
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 421.615 | 0.222417 | 6619.5ms | 1834197 | 30 | 2.55456e+09 | 4.14887e+06 | 0.0225601 | 12.0426 | 56.4599 | 12.6609 | 0.042831 | 0.32269 | 0.0107458 | 1(Win) | true |
| simdjson (ondemand) | 284.922 | 0.0904808 | 9586.82ms | 1834197 | 80 | 2.46856e+09 | 6.13932e+06 | 0.132606 | 17.743 | 98.2756 | 20.2762 | 0.0408958 | 0.767476 | 0.00522582 | 2(Loss) | true |
