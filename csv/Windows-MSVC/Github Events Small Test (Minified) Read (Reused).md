
----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1741.65 | 0.265025 | 119.594ms | 1691 | 320 | 1927.02 | 925.938 | 0.64538 | 1.70786 | 1(Win) | true |
| Glaze | 1647.02 | 0.169946 | 122.096ms | 1691 | 1280 | 3544.22 | 979.141 | 0.199872 | 1.81061 | 2(Loss) | true |
| Jsonifier (two-stage) | 1323.12 | 0.104111 | 153.802ms | 1691 | 4890 | 7873.87 | 1218.83 | 0.191416 | 2.2599 | 3(Loss) | true |
| simdjson (ondemand) | 876.708 | 0.132704 | 215.131ms | 1691 | 2560 | 15254.1 | 1839.45 | 0.42653 | 3.42844 | 4(Loss) | true |
