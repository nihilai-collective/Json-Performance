
----
### Twitter Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 877.969 | 0.21771 | 1029.16ms | 2821 | 40 | 1780.19 | 3064.25 | 0.00380749 | 5.94725 | 24.5537 | 4.57356 | 0.00212691 | 7.08968e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 351.434 | 0.0313486 | 1497.67ms | 2821 | 4890 | 28162 | 7655.26 | 0.0445638 | 14.6978 | 66.9273 | 11.5175 | 0.0145673 | 0.000162961 | 0.000104678 | 2(Loss) | true |
