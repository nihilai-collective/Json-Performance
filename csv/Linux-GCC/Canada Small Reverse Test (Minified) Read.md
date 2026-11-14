
----
### Canada Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 715.505 | 0.0707993 | 1342.7ms | 4630 | 2560 | 48869.2 | 6171.18 | 0.0520231 | 7.21837 | 35.7575 | 6.7108 | 0.00427232 | 9.05271e-05 | 4.47995e-05 | 1(Win) | true |
| Jsonifier (generic) | 635.202 | 0.0620834 | 1417.69ms | 4630 | 1280 | 23839.6 | 6951.35 | 0.0968713 | 8.14834 | 34.813 | 7.08942 | 0.0107873 | 4.70775e-05 | 2.05859e-05 | 2(Loss) | true |
