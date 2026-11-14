
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1486.54 | 0.063288 | 835.487ms | 1691 | 320 | 150.843 | 1084.84 | 0.133194 | 3.59703 | 13.1638 | 2.50917 | 0.00118273 | 0.000109033 | 3.69604e-06 | 1(Win) | true |
| simdjson (ondemand) | 1352.55 | 0.047101 | 845.77ms | 1691 | 4890 | 1542.23 | 1192.31 | 0.111045 | 3.93667 | 15.1892 | 2.51035 | 0.000597534 | 0.000132543 | 3.54336e-05 | 2(Loss) | true |
