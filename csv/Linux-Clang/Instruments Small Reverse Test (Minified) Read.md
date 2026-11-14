
----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 592.753 | 0.0377559 | 1472.18ms | 4669 | 1280 | 10296.3 | 7511.91 | 0.030484 | 8.73387 | 38.7169 | 7.68537 | 0.00894698 | 3.09555e-05 | 5.01981e-06 | 1(Win) | true |
| simdjson (ondemand) | 246.512 | 0.02629 | 2530.3ms | 4669 | 4890 | 110271 | 18062.9 | 0.0150035 | 20.9297 | 104.739 | 18.9589 | 0.0367356 | 5.16832e-05 | 6.70129e-06 | 2(Loss) | true |
