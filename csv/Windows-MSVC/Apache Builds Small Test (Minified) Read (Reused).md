
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1490.83 | 0.167038 | 202.964ms | 2632 | 1280 | 10124.1 | 1683.67 | 0.283853 | 2.015 | 1(Win) | true |
| Jsonifier (two-stage) | 1453.67 | 0.214937 | 200.859ms | 2632 | 640 | 8815.51 | 1726.72 | 0.0271542 | 2.06923 | 2(Loss) | true |
| Glaze | 1408.18 | 0.118919 | 211.967ms | 2632 | 4890 | 21972.1 | 1782.49 | 0.181934 | 2.13494 | 3(Loss) | true |
| simdjson (ondemand) | 1041.81 | 0.113685 | 268.004ms | 2632 | 4890 | 36687 | 2409.35 | 0.0344602 | 2.89336 | 4(Loss) | true |
