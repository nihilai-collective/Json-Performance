
----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 620.573 | 0.0660491 | 8829.87ms | 108313 | 320 | 3.86776e+06 | 166452 | 0.0624746 | 8.20566 | 38.0687 | 7.59222 | 0.0130083 | 1.17137e-05 | 4.5297e-06 | 1(Win) | true |
| simdjson (ondemand) | 247.729 | 0.0883777 | 5399.22ms | 108313 | 320 | 4.34552e+07 | 416968 | 0.0310262 | 20.6373 | 100.108 | 18.134 | 0.0682448 | 3.74205e-05 | 2.11771e-05 | 2(Loss) | true |
