
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2094.59 | 0.287237 | 183.888ms | 3370 | 640 | 12431.5 | 1534.38 | 0.182964 | 1.43298 | 1(Win) | true |
| Jsonifier (two-stage) | 1953.73 | 0.340258 | 196.727ms | 3370 | 80 | 2506.33 | 1645 | 0 | 1.53686 | 2(Loss) | true |
| Glaze | 1930.26 | 0.458716 | 202.246ms | 3370 | 40 | 2333.33 | 1665 | 0.1 | 1.55869 | 3(Loss) | true |
| simdjson (ondemand) | 1465.8 | 0.107151 | 255.228ms | 3370 | 2560 | 14130.1 | 2192.58 | 0.142323 | 2.05286 | 4(Loss) | true |
