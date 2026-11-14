
----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1717 | 0.104815 | 7566.68ms | 4197496 | 40 | 2.38863e+08 | 2.33141e+06 | 0.00873214 | 2.95402 | 14.6093 | 2.88738 | 0.000503336 | 0.0817154 | 0.000627261 | 1(Win) | true |
| simdjson (ondemand) | 1560.56 | 0.193655 | 8219.58ms | 4197496 | 80 | 1.9741e+09 | 2.56514e+06 | 0.400992 | 3.23227 | 16.5063 | 2.69504 | 0.00343208 | 0.0808823 | 0.000344086 | 2(Loss) | true |
