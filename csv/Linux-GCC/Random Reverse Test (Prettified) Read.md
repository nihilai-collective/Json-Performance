
----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1246.35 | 0.0788031 | 6697.3ms | 676745 | 320 | 5.32849e+07 | 517826 | 0.0436961 | 4.07932 | 18.3039 | 3.67616 | 0.00759227 | 0.0292289 | 5.60034e-05 | 1(Win) | true |
| simdjson (ondemand) | 794.357 | 0.148345 | 5167.16ms | 676745 | 40 | 5.81067e+07 | 812474 | 0.330901 | 6.41436 | 28.7122 | 5.69204 | 0.0190927 | 0.0459968 | 0.000116329 | 2(Loss) | true |
