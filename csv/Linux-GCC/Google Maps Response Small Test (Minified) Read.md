
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2060.96 | 0.107853 | 213.375ms | 4390 | 80 | 384.015 | 2031.4 | 0.178767 | 1.1859 | 1(Win) | true |
| Glaze | 1745.47 | 0.16339 | 247.579ms | 4390 | 40 | 614.353 | 2398.57 | 0.0977228 | 1.40318 | 2(Loss) | true |
| Jsonifier (two-stage) | 1563.2 | 0.095369 | 267.592ms | 4390 | 40 | 260.962 | 2678.25 | 0.246413 | 1.56782 | 3(Loss) | true |
| simdjson (reflection) | 1406.36 | 0.205106 | 299.711ms | 4390 | 2560 | 95440 | 2976.92 | 0.048653 | 1.74426 | 4(Loss) | true |
| simdjson (ondemand) | 1201.26 | 0.0799531 | 385.78ms | 4390 | 80 | 621.182 | 3485.21 | 0.136116 | 2.04526 | 5(Loss) | true |
