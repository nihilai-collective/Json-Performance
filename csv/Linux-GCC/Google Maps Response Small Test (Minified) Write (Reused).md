
----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 13890.1 | 0.0407023 | 32.9672ms | 4390 | 1280 | 19.2648 | 301.41 | 0.138996 | 0.162659 | 1(Win) | true |
| simdjson (reflection) | 11191.2 | 0.142783 | 41.4986ms | 4390 | 80 | 22.8253 | 374.1 | 0.456498 | 0.205339 | 2(Loss) | true |
| Glaze | 3588.25 | 0.244698 | 106.871ms | 4390 | 160 | 1304.21 | 1166.76 | 0.195365 | 0.672462 | 3(Loss) | true |
