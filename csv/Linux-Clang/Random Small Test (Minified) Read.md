
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1714.74 | 0.168724 | 1019.58ms | 5094 | 1280 | 29247 | 2833.09 | 0.0786532 | 2.99121 | 13.4572 | 2.44582 | 0.000778489 | 0.000101222 | 4.96908e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1530.34 | 0.118421 | 1057.87ms | 5094 | 2560 | 36177.7 | 3174.47 | 0.14835 | 3.33217 | 14.5024 | 2.60954 | 0.00184868 | 6.5871e-05 | 2.84495e-05 | 2(Loss) | true |
| Glaze | 1265.83 | 0.108348 | 1126.51ms | 5094 | 2560 | 44263.7 | 3837.82 | 0.028487 | 4.03523 | 16.4772 | 3.17491 | 0.00382098 | 0.000100992 | 4.14857e-05 | 3(Loss) | true |
| simdjson (ondemand) | 842.552 | 0.0742074 | 1321.72ms | 5094 | 4890 | 89521.6 | 5765.84 | 0.133467 | 6.04118 | 22.4358 | 3.82391 | 0.00603232 | 0.000194543 | 0.000100162 | 4(Loss) | true |
