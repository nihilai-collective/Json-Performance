
----
### Google Maps Response Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 840.393 | 0.106385 | 2082.6ms | 11812 | 30 | 6100.44 | 13404.2 | 0.167577 | 6.14835 | 28.6371 | 5.80084 | 0.0143329 | 6.49057e-05 | 3.38639e-05 | 1(Win) | true |
| simdjson (ondemand) | 725.213 | 0.0644094 | 2296.57ms | 11812 | 320 | 32030.5 | 15533.1 | 0.0976289 | 7.11643 | 31.4302 | 6.1374 | 0.0142974 | 2.91018e-05 | 1.0847e-05 | 2(Loss) | true |
