
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1105.32 | 0.238071 | 1231.19ms | 4604 | 320 | 28619 | 3972.33 | 0.0410034 | 4.6192 | 18.7609 | 4.03019 | 0.00626697 | 3.12228e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 903.706 | 0.125449 | 1323ms | 4604 | 1280 | 47551.2 | 4858.57 | 0.180251 | 5.64845 | 23.1844 | 4.65465 | 0.00646669 | 3.56348e-05 | 1.69689e-06 | 2(Loss) | true |
| Glaze | 745.772 | 0.151782 | 1421.81ms | 4604 | 160 | 12776.7 | 5887.48 | 0.0408873 | 6.82441 | 28.6464 | 5.70873 | 0.00597985 | 7.33058e-05 | 1.90052e-05 | 3(Loss) | true |
| simdjson (ondemand) | 550.077 | 0.111657 | 1639.05ms | 4604 | 1280 | 101672 | 7982 | 0.0187077 | 9.23389 | 37.2391 | 6.50429 | 0.00938094 | 6.27851e-05 | 1.98537e-05 | 4(Loss) | true |
