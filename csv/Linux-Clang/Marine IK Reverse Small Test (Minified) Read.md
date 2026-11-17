
----
### Marine IK Reverse Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 756.362 | 0.137232 | 1322.87ms | 4604 | 2560 | 162466 | 5805.05 | 0.00568573 | 6.74619 | 26.1755 | 5.74609 | 0.00527471 | 0.000154842 | 8.64567e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 663.18 | 0.11065 | 1407.72ms | 4604 | 4890 | 262433 | 6620.7 | 0.0881486 | 7.65384 | 30.3189 | 6.2765 | 0.00689624 | 0.000392741 | 0.000235725 | 2(Loss) | true |
| Glaze | 621.076 | 0.055157 | 1449.47ms | 4604 | 4890 | 74351.8 | 7069.54 | 0.0869804 | 8.17509 | 34.0867 | 6.94983 | 0.00473568 | 7.82195e-05 | 2.68283e-05 | 3(Loss) | true |
| simdjson (ondemand) | 508.37 | 0.298911 | 1608.57ms | 4604 | 320 | 213277 | 8636.85 | 0.0905736 | 9.98739 | 40.5563 | 7.26542 | 0.00577283 | 0.000397073 | 0.000266752 | 4(Loss) | true |
