
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1412.17 | 0.180123 | 360.575ms | 4390 | 320 | 9125.29 | 2964.69 | 0.555556 | 1.73634 | 1(Win) | true |
| Jsonifier (two-stage) | 1210.66 | 0.118809 | 397.98ms | 4390 | 160 | 2700.86 | 3458.12 | 0.162925 | 2.02877 | 2(Loss) | true |
| Glaze | 995.336 | 0.238197 | 487.204ms | 4390 | 160 | 16061.3 | 4206.25 | 0.0594707 | 2.47485 | 3(Loss) | true |
| simdjson (ondemand) | 687.46 | 0.298239 | 671.822ms | 4390 | 30 | 9896.55 | 6090 | 0.550358 | 3.58686 | 4(Loss) | true |
