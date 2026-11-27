
----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1481.55 | 0.0438637 | 1027.67ms | 4669 | 320 | 556.127 | 3005.43 | 0.0889264 | 3.52401 | 14.5768 | 2.78239 | 0.00207753 | 3.54733e-05 | 6.02377e-06 | 1(Win) | true |
| simdjson (ondemand) | 1448.75 | 0.142569 | 1033.19ms | 4669 | 80 | 1536.02 | 3073.47 | 0.0488285 | 3.60388 | 16.2722 | 2.41829 | 0.00180713 | 7.76398e-05 | 2.67723e-05 | 2(Loss) | true |
