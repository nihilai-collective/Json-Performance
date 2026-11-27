
----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2389.63 | 0.38634 | 139.768ms | 2889 | 640 | 12698.5 | 1152.97 | 0.283784 | 1.24945 | 1(Win) | true |
| Glaze | 2004.95 | 0.106013 | 158.045ms | 2889 | 2560 | 5433.09 | 1374.18 | 0.173099 | 1.49453 | 2(Loss) | true |
| Jsonifier (two-stage) | 1595.33 | 0.157758 | 199.817ms | 2889 | 4890 | 36298.1 | 1727.01 | 1.71276 | 1.88255 | 3(Loss) | true |
| simdjson (ondemand) | 1563.35 | 0.557957 | 195.678ms | 2889 | 640 | 61881.8 | 1762.34 | 0.00886682 | 1.92435 | 4(Loss) | true |
