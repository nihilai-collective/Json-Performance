
----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 569.825 | 0.0825691 | 1517.11ms | 4669 | 160 | 6660.7 | 7814.16 | 0.112888 | 9.25618 | 39.0722 | 7.81238 | 0.0108093 | 6.02377e-05 | 3.07882e-05 | 1(Win) | true |
| simdjson (ondemand) | 246.828 | 0.0338322 | 2522.22ms | 4669 | 1280 | 47679.5 | 18039.7 | 0.00161105 | 20.8807 | 94.8415 | 19.4065 | 0.0486691 | 4.56803e-05 | 9.20299e-06 | 2(Loss) | true |
