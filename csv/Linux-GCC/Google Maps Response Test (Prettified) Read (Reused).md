
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2818.6 | 0.0410305 | 1648.18ms | 25388 | 2560 | 31801.2 | 8590.04 | 0.163421 | 1.83003 | 8.62435 | 1.49035 | 0.00267103 | 2.01559e-05 | 7.93928e-06 | 1(Win) | true |
| simdjson (ondemand) | 2322.62 | 0.05692 | 1821.26ms | 25388 | 80 | 2816.56 | 10424.4 | 0.0803959 | 2.22752 | 9.37616 | 1.62998 | 0.00349378 | 1.2309e-05 | 5.9083e-06 | 2(Loss) | true |
