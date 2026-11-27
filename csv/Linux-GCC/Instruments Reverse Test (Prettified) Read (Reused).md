
----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1049.33 | 0.128191 | 9052.05ms | 183677 | 80 | 3.66342e+06 | 166933 | 0.0265081 | 4.87296 | 22.6683 | 4.45055 | 0.00505806 | 0.000105688 | 8.28901e-05 | 1(Win) | true |
| simdjson (ondemand) | 432.533 | 0.10245 | 5252.26ms | 183677 | 80 | 1.37715e+07 | 404982 | 0.102501 | 11.7565 | 52.8927 | 10.6264 | 0.0479079 | 4.11048e-05 | 3.15772e-05 | 2(Loss) | true |
