
----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 832.778 | 0.0548117 | 1302.37ms | 4857 | 640 | 5948.46 | 5562.1 | 0.046345 | 6.22951 | 28.0752 | 5.48672 | 0.00585495 | 2.41275e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 236.137 | 0.0410038 | 2711.38ms | 4857 | 640 | 41403.6 | 19615.7 | 0.0230151 | 21.8444 | 113.469 | 21.8231 | 0.0449647 | 4.95419e-05 | 3.21701e-06 | 2(Loss) | true |
