
----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11948.2 | 0.0467273 | 764.452ms | 4669 | 160 | 4.85185 | 372.669 | 0.0754123 | 0.468609 | 1.25594 | 0.317199 | 0.000214179 | 1.47248e-05 | 2.67723e-06 | 1(Win) | true |
| simdjson (reflection) | 7831.2 | 0.142019 | 784.416ms | 4669 | 2560 | 1669.25 | 568.585 | 0.392523 | 0.698213 | 1.68002 | 0.225316 | 0.000214681 | 1.61471e-05 | 6.1911e-06 | 2(Loss) | true |
| Glaze | 3572.27 | 0.134376 | 860.119ms | 4669 | 1280 | 3591 | 1246.46 | 0.109554 | 1.46181 | 3.4607 | 0.498822 | 0.000215685 | 5.2708e-05 | 1.72347e-05 | 3(Loss) | true |
