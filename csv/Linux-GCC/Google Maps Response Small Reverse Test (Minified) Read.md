
----
### Google Maps Response Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 752.63 | 0.0318388 | 1274.22ms | 4390 | 2560 | 8030.09 | 5562.67 | 0.0101482 | 6.88794 | 29.4153 | 5.96606 | 0.0120032 | 4.01303e-05 | 5.5168e-06 | 1(Win) | true |
| simdjson (ondemand) | 713.664 | 0.0273803 | 1304.27ms | 4390 | 4890 | 12616.1 | 5866.39 | 0.269436 | 7.26113 | 31.6255 | 6.16287 | 0.00624481 | 3.86172e-05 | 5.68312e-06 | 2(Loss) | true |
