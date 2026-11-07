
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2225.53 | 0.0331744 | 127.458ms | 2889 | 640 | 107.948 | 1237.98 | 0.0359838 | 1.08869 | 1(Win) | true |
| Jsonifier (two-stage) | 2212.04 | 0.147828 | 128.184ms | 2889 | 30 | 101.706 | 1245.53 | 0.352019 | 1.09553 | 2(Loss) | true |
| Glaze | 2146.94 | 0.496998 | 135.366ms | 2889 | 30 | 1220.36 | 1283.3 | 0.178905 | 1.13029 | 3(Loss) | true |
| simdjson (ondemand) | 1020.8 | 0.054774 | 280.418ms | 2889 | 80 | 174.847 | 2699.04 | 0.0542154 | 2.40241 | 4(Loss) | true |
