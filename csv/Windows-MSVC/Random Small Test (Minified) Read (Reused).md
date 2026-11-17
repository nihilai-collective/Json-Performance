
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 993.522 | 0.0654425 | 581.26ms | 5094 | 4890 | 50071.7 | 4889.69 | 0.0038766 | 3.04832 | 1(Win) | true |
| Jsonifier (two-stage) | 866.63 | 0.0620136 | 660.417ms | 5094 | 4890 | 59092.7 | 5605.64 | 0.0358938 | 3.49407 | 2(Loss) | true |
| Glaze | 814.57 | 0.129778 | 695.09ms | 5094 | 1280 | 76679 | 5963.91 | 0.0314292 | 3.71931 | 3(Loss) | true |
| simdjson (ondemand) | 579.375 | 0.0526887 | 949.194ms | 5094 | 4890 | 95442.7 | 8384.93 | 0.221184 | 5.23319 | 4(Loss) | true |
