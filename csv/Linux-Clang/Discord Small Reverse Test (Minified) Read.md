
----
### Discord Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 722.201 | 0.0442261 | 1363.43ms | 4857 | 640 | 5149.4 | 6413.72 | 0.0466312 | 7.17608 | 31.1437 | 6.15483 | 0.00629407 | 4.37513e-05 | 8.04252e-06 | 1(Win) | true |
| simdjson (ondemand) | 229.152 | 0.0136427 | 2745.91ms | 4857 | 4890 | 37187.4 | 20213.6 | 0.0192868 | 22.5127 | 115.762 | 22.3167 | 0.0437075 | 0.00011267 | 3.67147e-05 | 2(Loss) | true |
