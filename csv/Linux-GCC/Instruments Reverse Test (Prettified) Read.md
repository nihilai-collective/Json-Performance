
----
### Instruments Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1008.31 | 0.0251426 | 9254.74ms | 183677 | 2560 | 4.88407e+06 | 173724 | 0.092416 | 5.04599 | 23.0713 | 4.54365 | 0.00534895 | 4.09112e-05 | 3.16559e-05 | 1(Win) | true |
| simdjson (ondemand) | 428.635 | 0.0526285 | 5304.14ms | 183677 | 320 | 1.48022e+07 | 408664 | 0.0899356 | 11.9275 | 53.2919 | 10.719 | 0.0489417 | 6.58765e-05 | 4.68213e-05 | 2(Loss) | true |
