
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1369.72 | 0.0343346 | 1550.77ms | 11812 | 4890 | 38990.4 | 8224.17 | 0.135339 | 3.71671 | 17.695 | 3.32306 | 0.0045523 | 4.66234e-05 | 2.43938e-05 | 1(Win) | true |
| simdjson (ondemand) | 1066.13 | 0.0448907 | 1786.99ms | 11812 | 2560 | 57594.5 | 10566.1 | 0.169846 | 4.80578 | 19.646 | 3.66767 | 0.00908977 | 4.41818e-05 | 1.91146e-05 | 2(Loss) | true |
