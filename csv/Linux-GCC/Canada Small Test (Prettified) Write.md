
----
### Canada Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6294.73 | 0.0549602 | 946.36ms | 14795 | 4890 | 7421.33 | 2241.5 | 0.057273 | 0.834073 | 2.50085 | 0.129436 | 6.81018e-05 | 2.62898e-05 | 1.03252e-05 | 1(Win) | true |
| Glaze | 3586.5 | 0.104638 | 1126.28ms | 14795 | 320 | 5422.73 | 3934.09 | 0.0281275 | 1.42483 | 4.53282 | 0.518756 | 6.80128e-05 | 1.4363e-05 | 1.26732e-06 | 2(Loss) | true |
| simdjson (reflection) | 474.368 | 0.102827 | 3714.11ms | 14795 | 2560 | 2.39469e+06 | 29744 | 0.0924938 | 10.8041 | 37.6348 | 5.21737 | 0.00430712 | 8.75771e-05 | 4.14255e-05 | 3(Loss) | true |
