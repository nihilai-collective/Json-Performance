
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1846.01 | 0.198552 | 167.469ms | 2889 | 80 | 702.532 | 1492.5 | 0.167785 | 1.32012 | 1(Win) | true |
| Jsonifier (two-stage) | 1497.88 | 0.452274 | 204.259ms | 2889 | 2560 | 177167 | 1839.38 | 0.687561 | 1.628 | 2(Loss) | true |
| Glaze | 1452 | 0.186915 | 210.2ms | 2889 | 80 | 1006.33 | 1897.5 | 0.396825 | 1.68573 | 3(Loss) | true |
| simdjson (ondemand) | 1316.69 | 0.204299 | 235.733ms | 2889 | 80 | 1462.03 | 2092.5 | 0.475624 | 1.86246 | 4(Loss) | true |
