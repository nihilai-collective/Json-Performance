
----
### Instruments Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5413.19 | 0.0197854 | 3964.73ms | 183677 | 4890 | 200447 | 32359.5 | 0.0266958 | 0.947949 | 5.20744 | 0.878831 | 0.000588292 | 3.5494e-06 | 1.91053e-06 | 1(Win) | true |
| simdjson (ondemand) | 4115.94 | 0.021476 | 4975.01ms | 183677 | 2560 | 213855 | 42558.4 | 0.000446994 | 1.23589 | 6.40472 | 0.975321 | 0.00217537 | 4.52561e-06 | 2.70303e-06 | 2(Loss) | true |
