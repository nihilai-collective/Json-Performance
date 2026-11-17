
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2292.97 | 0.0505243 | 79.1628ms | 1691 | 640 | 80.8112 | 703.308 | 0.152837 | 1.03937 | 1(Win) | true |
| Jsonifier | 2240.35 | 0.217613 | 81.1909ms | 1691 | 40 | 98.1481 | 719.825 | 0.059077 | 1.05934 | 2(Loss) | true |
| simdjson (reflection) | 2037.3 | 0.0664731 | 88.8859ms | 1691 | 640 | 177.194 | 791.569 | 0.441734 | 1.17023 | 3(Loss) | true |
| Glaze | 1679.99 | 0.121177 | 102.658ms | 1691 | 40 | 54.1224 | 959.925 | 0.0182273 | 1.43028 | 4(Loss) | true |
| simdjson (ondemand) | 1457.42 | 0.176169 | 119.003ms | 1691 | 160 | 607.987 | 1106.52 | 0.236092 | 1.65496 | 5(Loss) | true |
