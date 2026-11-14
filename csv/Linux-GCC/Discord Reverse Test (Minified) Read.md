
----
### Discord Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 646.076 | 0.0996651 | 9021.44ms | 56369 | 160 | 1.10032e+06 | 83206.5 | 0.110299 | 7.89173 | 35.0405 | 7.34068 | 0.0123824 | 1.04224e-05 | 2.77191e-06 | 1(Win) | true |
| simdjson (ondemand) | 209.89 | 0.0777162 | 6709.79ms | 56369 | 320 | 1.26785e+07 | 256123 | 0.0812256 | 24.2391 | 132.848 | 28.2488 | 0.0373043 | 0.000100565 | 4.59029e-05 | 2(Loss) | true |
