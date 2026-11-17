
----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15150.9 | 0.110402 | 30.8605ms | 4390 | 320 | 29.7823 | 276.328 | 0.0531242 | 0.148124 | 1(Win) | true |
| simdjson (reflection) | 11056.7 | 0.18471 | 40.3443ms | 4390 | 40 | 19.5667 | 378.65 | 0.0132066 | 0.207728 | 2(Loss) | true |
| Glaze | 3828.59 | 0.0707051 | 111.057ms | 4390 | 160 | 95.6474 | 1093.52 | 0.000571546 | 0.630256 | 3(Loss) | true |
