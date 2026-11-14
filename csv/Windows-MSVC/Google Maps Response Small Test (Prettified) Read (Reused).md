
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2416.36 | 0.176553 | 418.447ms | 9378 | 80 | 3416.14 | 3701.25 | 0.101215 | 1.25023 | 1(Win) | true |
| Jsonifier | 2216.67 | 0.207301 | 455.275ms | 9378 | 4890 | 342082 | 4034.68 | 0.0386308 | 1.36481 | 2(Loss) | true |
| Glaze | 1718.13 | 0.178891 | 566.86ms | 9378 | 4890 | 424029 | 5205.4 | 0.261234 | 1.76191 | 3(Loss) | true |
| simdjson (ondemand) | 1374.81 | 0.304626 | 703.095ms | 9378 | 640 | 251333 | 6505.31 | 0.062488 | 2.20398 | 4(Loss) | true |
