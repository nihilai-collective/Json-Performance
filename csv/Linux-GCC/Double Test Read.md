
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 614 | 0.0848285 | 995.919ms | 1811 | 320 | 1821.94 | 2812.88 | 0.034007 | 8.52092 | 41.4809 | 5.98454 | 0.000560809 | 0.000139771 | 6.72971e-05 | 1(Win) | true |
| simdjson (ondemand) | 331.077 | 0.0934575 | 1243.43ms | 1811 | 640 | 15212 | 5216.62 | 0.0151582 | 15.6635 | 77.2275 | 9.76091 | 0.000604811 | 6.98854e-05 | 4.31391e-06 | 2(Loss) | true |
