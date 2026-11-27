
----
### Github Events Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 944.709 | 0.092556 | 899.923ms | 1691 | 640 | 1597.64 | 1707.05 | 0.122686 | 5.57987 | 19.8386 | 4.08161 | 0.00152092 | 9.6097e-05 | 1.66322e-05 | 1(Win) | true |
| simdjson (ondemand) | 686.459 | 0.115067 | 964.128ms | 1691 | 4890 | 35733 | 2349.25 | 7.0863e-05 | 7.62716 | 30.1396 | 5.39503 | 0.00295792 | 0.00010485 | 3.20474e-05 | 2(Loss) | true |
