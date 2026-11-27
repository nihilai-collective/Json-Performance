
----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 949.035 | 0.0441536 | 1288.25ms | 4630 | 2560 | 10803.7 | 4652.63 | 0.110048 | 5.41952 | 26.7382 | 4.6743 | 0.00219113 | 3.071e-05 | 9.19614e-06 | 1(Win) | true |
| Jsonifier (generic) | 875.28 | 0.0469711 | 1331.82ms | 4630 | 80 | 449.18 | 5044.69 | 0.0245368 | 5.93413 | 26.5158 | 5.23175 | 0.00458153 | 1.61987e-05 | 8.09935e-06 | 2(Loss) | true |
