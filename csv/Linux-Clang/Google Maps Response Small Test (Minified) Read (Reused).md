
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2515.76 | 0.45759 | 181.141ms | 4390 | 80 | 4639.1 | 1664.16 | 0.355518 | 0.96707 | 1(Win) | true |
| Jsonifier (two-stage) | 1945.87 | 0.821482 | 233.255ms | 4390 | 320 | 99965.3 | 2151.55 | 0.168476 | 1.2555 | 2(Loss) | true |
| Glaze | 1738.76 | 0.321482 | 259.087ms | 4390 | 2560 | 153391 | 2407.82 | 0.361636 | 1.40744 | 3(Loss) | true |
| simdjson (ondemand) | 996.569 | 0.215853 | 440.711ms | 4390 | 2560 | 210509 | 4201.04 | 0.144462 | 2.46676 | 4(Loss) | true |
