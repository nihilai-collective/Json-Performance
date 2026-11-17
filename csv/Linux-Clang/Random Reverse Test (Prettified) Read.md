
----
### Random Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1207.75 | 0.0603554 | 6897.13ms | 676745 | 640 | 6.65744e+07 | 534377 | 0.0376757 | 4.22634 | 18.5633 | 3.71962 | 0.0100438 | 0.0251758 | 4.23027e-05 | 1(Win) | true |
| simdjson (ondemand) | 724.115 | 0.0531672 | 5671.79ms | 676745 | 320 | 7.18575e+07 | 891287 | 0.00573817 | 7.03765 | 30.9378 | 5.61399 | 0.0251598 | 0.0440987 | 0.000117936 | 2(Loss) | true |
