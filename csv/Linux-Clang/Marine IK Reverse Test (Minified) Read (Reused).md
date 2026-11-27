
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 410.758 | 0.193025 | 6812.63ms | 1834197 | 30 | 2.02706e+09 | 4.25853e+06 | 0.0515106 | 12.298 | 58.6197 | 12.8453 | 0.0427448 | 0.322859 | 0.0020727 | 1(Win) | true |
| simdjson (ondemand) | 285.181 | 0.0870662 | 9691.16ms | 1834197 | 80 | 2.2816e+09 | 6.13374e+06 | 0.388591 | 17.8336 | 101.946 | 20.4362 | 0.0385444 | 0.767757 | 0.0154815 | 2(Loss) | true |
