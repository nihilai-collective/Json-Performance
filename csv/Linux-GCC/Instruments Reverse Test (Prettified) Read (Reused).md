
----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 907.639 | 0.0738617 | 5122.91ms | 183677 | 320 | 6.50238e+06 | 192993 | 0.0566144 | 5.61934 | 23.5689 | 4.71816 | 0.0058125 | 6.58425e-06 | 1.97357e-06 | 1(Win) | true |
| simdjson (ondemand) | 441.64 | 0.0848428 | 5179.98ms | 183677 | 640 | 7.2474e+07 | 396630 | 0.0258281 | 11.5966 | 52.9764 | 10.6855 | 0.0445076 | 4.75274e-05 | 3.30063e-05 | 2(Loss) | true |
