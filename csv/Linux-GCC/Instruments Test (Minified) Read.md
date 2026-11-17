
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1650.26 | 0.0336292 | 7005.87ms | 108313 | 2560 | 1.13431e+06 | 62593.5 | 0.00600191 | 3.10124 | 13.8783 | 2.79373 | 0.00362751 | 2.39648e-05 | 1.63516e-05 | 1(Win) | true |
| simdjson (ondemand) | 1502.14 | 0.0475467 | 7633.25ms | 108313 | 1280 | 1.36832e+06 | 68765.2 | 0.0520977 | 3.40221 | 15.2886 | 2.51076 | 0.00541413 | 1.47936e-05 | 9.3984e-06 | 2(Loss) | true |
