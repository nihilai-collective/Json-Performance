
----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1248.85 | 0.0346122 | 1343.52ms | 8150 | 2560 | 11879.4 | 6223.69 | 0.000207122 | 4.14862 | 17.4442 | 3.4789 | 0.0055995 | 2.48275e-05 | 4.21779e-06 | 1(Win) | true |
| simdjson (ondemand) | 827.836 | 0.0747659 | 1657.7ms | 8150 | 320 | 15768.3 | 9388.88 | 0.0328955 | 6.24489 | 27.7063 | 5.4589 | 0.0113052 | 1.57209e-05 | 2.68405e-06 | 2(Loss) | true |
