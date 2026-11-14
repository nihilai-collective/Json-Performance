
----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2027.88 | 0.255302 | 6987.67ms | 4219120 | 30 | 7.69822e+08 | 1.98418e+06 | 0.0307808 | 2.49578 | 9.19097 | 1.59769 | 0.0145595 | 0.0564623 | 5.16221e-05 | 1(Win) | true |
| simdjson (ondemand) | 1859.42 | 0.0662406 | 7516.54ms | 4219120 | 160 | 3.28743e+08 | 2.16393e+06 | 0.0100513 | 2.71008 | 9.41697 | 1.53176 | 0.0148131 | 0.0534411 | 0.000242447 | 2(Loss) | true |
