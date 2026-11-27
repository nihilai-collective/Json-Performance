
----
### Google Maps Response Stream Reverse Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 861.394 | 0.795445 | 7542.89ms | 4203059 | 30 | 4.11026e+10 | 4.65333e+06 | 0.250616 | 5.91705 | 26.7813 | 5.3214 | 0.0242149 | 0.0878765 | 0.00779063 | 1(Win) | true |
| simdjson (ondemand) | 771.712 | 0.484831 | 8215.9ms | 4203059 | 80 | 5.0733e+10 | 5.1941e+06 | 0.12438 | 6.5763 | 26.5741 | 5.07451 | 0.0265552 | 0.0866345 | 0.00838048 | 2(Loss) | true |
