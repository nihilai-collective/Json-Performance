
----
### Canada Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6513.79 | 0.0658916 | 939.222ms | 14795 | 320 | 651.887 | 2166.11 | 0.0225108 | 0.806059 | 2.46157 | 0.120514 | 6.80128e-05 | 9.71612e-06 | 8.4488e-07 | 1(Win) | true |
| Glaze | 3906.03 | 0.0811206 | 1090.86ms | 14795 | 4890 | 41988.5 | 3612.27 | 0.244547 | 1.31861 | 4.33721 | 0.47462 | 0.000132707 | 1.35457e-05 | 3.51083e-06 | 2(Loss) | true |
| simdjson (reflection) | 470.224 | 0.0974488 | 3744.47ms | 14795 | 2560 | 2.18883e+06 | 30006.1 | 0.0183301 | 10.8612 | 37.6661 | 5.2246 | 0.00438105 | 9.3148e-05 | 5.21449e-05 | 3(Loss) | true |
