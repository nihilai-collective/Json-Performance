
----
### Twitter Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2716.47 | 0.0523806 | 849.624ms | 3770 | 2560 | 1230.42 | 1323.54 | 0.0498735 | 1.95348 | 7.31379 | 1.26976 | 0.000268878 | 4.71444e-05 | 1.23301e-05 | 1(Win) | true |
| simdjson (ondemand) | 2589.38 | 0.0638509 | 857.345ms | 3770 | 160 | 125.761 | 1388.5 | 0.0332982 | 2.04735 | 7.83289 | 1.17958 | 0.000265252 | 3.64721e-05 | 0 | 2(Loss) | true |
