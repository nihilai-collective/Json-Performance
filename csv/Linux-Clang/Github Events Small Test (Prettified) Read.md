
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1507.52 | 0.0534865 | 853.31ms | 2158 | 2560 | 1364.92 | 1365.18 | 0.05176 | 3.51602 | 12.3809 | 2.39296 | 0.000480588 | 8.16366e-05 | 1.21278e-05 | 1(Win) | true |
| simdjson (ondemand) | 1474 | 0.0398323 | 856.145ms | 2158 | 2560 | 791.804 | 1396.22 | 0.0302344 | 3.59536 | 13.4666 | 2.30538 | 0.000477692 | 0.000113857 | 4.07278e-05 | 2(Loss) | true |
