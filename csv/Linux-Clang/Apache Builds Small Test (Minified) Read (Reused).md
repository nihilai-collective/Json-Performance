
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2391.67 | 0.0901294 | 831.63ms | 2632 | 2560 | 2290.57 | 1049.51 | 0.00628976 | 2.23545 | 9.13564 | 1.64096 | 0.00076344 | 4.31884e-05 | 4.304e-06 | 1(Win) | true |
| simdjson (ondemand) | 1888.97 | 0.0911347 | 860.819ms | 2632 | 1280 | 1877.15 | 1328.8 | 0.0053505 | 2.8092 | 10.4069 | 1.7234 | 0.00283381 | 6.58957e-05 | 1.5435e-05 | 2(Loss) | true |
