
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1399.33 | 0.26297 | 352.285ms | 4390 | 320 | 19808.4 | 2991.88 | 0.208464 | 2.16045 | 1(Win) | true |
| Jsonifier (two-stage) | 1175.41 | 0.0806577 | 410.793ms | 4390 | 4890 | 40359.9 | 3561.84 | 0.00206551 | 2.5711 | 2(Loss) | true |
| Glaze | 1124.68 | 0.311497 | 427.848ms | 4390 | 40 | 5378.21 | 3722.5 | 0.0223814 | 2.69311 | 3(Loss) | true |
| simdjson (ondemand) | 612.78 | 0.191194 | 734.813ms | 4390 | 320 | 54603.4 | 6832.19 | 0.371867 | 4.94653 | 4(Loss) | true |
