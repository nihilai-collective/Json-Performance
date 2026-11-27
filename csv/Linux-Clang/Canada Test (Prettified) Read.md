
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 17392.9 | 0.466247 | 7781.27ms | 5373214 | 1280 | 2.41527e+09 | 294620 | 0.0874793 | 0.289991 | 1.42439 | 0.0692394 | 0.00101322 | 0.0195583 | 1.39421e-06 | 1(Win) | true |
| simdjson (stage-1) | 15414.8 | 0.202106 | 8811.83ms | 5373214 | 320 | 1.44445e+08 | 332428 | 0.294928 | 0.332152 | 1.41698 | 0.0578111 | 0.000945057 | 0.0195803 | 5.38202e-06 | 2(Loss) | true |
