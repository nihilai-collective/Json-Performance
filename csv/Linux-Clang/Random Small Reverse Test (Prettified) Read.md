
----
### Random Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1260.15 | 0.0596397 | 1347.76ms | 8150 | 640 | 8660.15 | 6167.89 | 0.00613091 | 4.11221 | 17.3065 | 3.47657 | 0.00613708 | 2.07055e-05 | 3.06748e-06 | 1(Win) | true |
| simdjson (ondemand) | 738.626 | 0.033785 | 1781.45ms | 8150 | 2560 | 32355.9 | 10522.8 | 0.14639 | 6.97395 | 29.9496 | 5.37742 | 0.0175818 | 7.65913e-05 | 3.84394e-05 | 2(Loss) | true |
