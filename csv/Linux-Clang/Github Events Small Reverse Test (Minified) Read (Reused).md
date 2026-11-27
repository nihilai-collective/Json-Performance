
----
### Github Events Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1061.55 | 0.130409 | 889.278ms | 1691 | 640 | 2511.9 | 1519.15 | 0.115225 | 4.96355 | 18.3903 | 3.71851 | 0.000926781 | 6.37567e-05 | 1.84802e-06 | 1(Win) | true |
| simdjson (ondemand) | 736.847 | 0.0989452 | 947.126ms | 1691 | 640 | 3001.25 | 2188.6 | 0.244421 | 7.11656 | 28.5411 | 5.00237 | 0.00357961 | 7.39208e-05 | 4.62005e-06 | 2(Loss) | true |
