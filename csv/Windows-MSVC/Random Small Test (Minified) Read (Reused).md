
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1056.09 | 0.122292 | 584.004ms | 5094 | 80 | 2531.65 | 4600 | 0 | 2.33049 | 1(Win) | true |
| Jsonifier (two-stage) | 913.734 | 0.158353 | 651.263ms | 5094 | 30 | 2126.44 | 5316.67 | 0 | 2.69576 | 2(Loss) | true |
| Glaze | 816.473 | 0.238365 | 708.207ms | 5094 | 30 | 6034.48 | 5950 | 0.055991 | 3.02837 | 3(Loss) | true |
| simdjson (ondemand) | 636.908 | 0.125541 | 871.923ms | 5094 | 80 | 7335.44 | 7627.5 | 0 | 3.87969 | 4(Loss) | true |
