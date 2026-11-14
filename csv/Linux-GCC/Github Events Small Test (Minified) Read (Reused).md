
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1471.12 | 0.038483 | 835.283ms | 1691 | 4890 | 870.245 | 1096.22 | 0.0318523 | 3.63125 | 13.1821 | 2.46008 | 0.00101415 | 7.81232e-05 | 7.61883e-06 | 1(Win) | true |
| simdjson (ondemand) | 1413.32 | 0.073206 | 839ms | 1691 | 160 | 111.64 | 1141.04 | 0.00273865 | 3.7732 | 13.6334 | 2.47428 | 0.000595062 | 0.000110881 | 0 | 2(Loss) | true |
