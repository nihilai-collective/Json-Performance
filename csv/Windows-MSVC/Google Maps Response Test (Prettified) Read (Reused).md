
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2367.07 | 0.160962 | 1144.45ms | 25388 | 4890 | 1.32553e+06 | 10228.6 | 0.274058 | 1.04316 | 1(Win) | true |
| Jsonifier (two-stage) | 2216.53 | 0.104641 | 1213.73ms | 25388 | 30 | 3919.54 | 10923.3 | 0 | 1.11405 | 2(Loss) | true |
| Glaze | 1585.59 | 0.109447 | 1710.44ms | 25388 | 30 | 8379.31 | 15270 | 0.152572 | 1.55882 | 3(Loss) | true |
| simdjson (ondemand) | 1250.17 | 0.189925 | 1992.87ms | 25388 | 2560 | 3.46354e+06 | 19366.8 | 0.354425 | 1.97753 | 4(Loss) | true |
