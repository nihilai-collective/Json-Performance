
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2757.41 | 0.104437 | 83.1562ms | 2158 | 160 | 97.2137 | 746.362 | 0.0502185 | 0.863169 | 1(Win) | true |
| simdjson (reflection) | 2446.54 | 0.269313 | 95.8191ms | 2158 | 40 | 205.292 | 841.2 | 0.284495 | 0.976193 | 2(Loss) | true |
| Glaze | 2395.93 | 0.0591393 | 95.52ms | 2158 | 160 | 41.2883 | 858.969 | 0.491623 | 0.999838 | 3(Loss) | true |
| Jsonifier | 1947.85 | 0.213509 | 123.563ms | 2158 | 30 | 152.668 | 1056.57 | 1.09832 | 1.2377 | 4(Loss) | true |
| simdjson (ondemand) | 1873.2 | 0.188366 | 119.523ms | 2158 | 160 | 685.267 | 1098.67 | 0.269485 | 1.2886 | 5(Loss) | true |
