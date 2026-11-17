
----
### Instruments Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 23730 | 0.14 | 761.519ms | 9249 | 4890 | 1324.22 | 371.704 | 0.291159 | 0.237172 | 0.657152 | 0.1478 | 0.000108252 | 1.93024e-05 | 8.0924e-06 | 1(Win) | true |
| Glaze | 3420.33 | 0.429506 | 992.18ms | 9249 | 640 | 78518.6 | 2578.85 | 0.042127 | 1.51598 | 3.52752 | 0.565359 | 0.000378926 | 7.2643e-06 | 0 | 2(Loss) | true |
| simdjson (reflection) | 509.494 | 0.135506 | 2473.1ms | 9249 | 1280 | 704428 | 17312.3 | 0.0342314 | 9.96134 | 40.824 | 8.29744 | 0.0155013 | 0.000132785 | 7.30653e-05 | 3(Loss) | true |
