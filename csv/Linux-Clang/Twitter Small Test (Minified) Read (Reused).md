
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2641.31 | 0.273601 | 849.264ms | 2889 | 4890 | 39829 | 1043.1 | 0.206559 | 1.98192 | 6.15403 | 0.991001 | 0.0013932 | 5.98844e-05 | 1.50065e-05 | 1(Win) | true |
| Glaze | 2616.22 | 0.183114 | 853.359ms | 2889 | 4890 | 18184.3 | 1053.11 | 0.0300329 | 2.00766 | 8.16476 | 1.34995 | 0.000396186 | 6.08046e-05 | 1.1538e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2352.6 | 0.52448 | 864.259ms | 2889 | 1280 | 48291 | 1171.11 | 0.237788 | 2.22654 | 7.55002 | 1.12565 | 0.000958647 | 3.48845e-05 | 4.32676e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1047.29 | 0.104024 | 1009.73ms | 2889 | 4890 | 36621.5 | 2630.76 | 0.0826849 | 4.89353 | 16.4946 | 2.76428 | 0.000526289 | 6.25035e-05 | 1.33784e-05 | 4(Loss) | true |
