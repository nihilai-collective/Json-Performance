
----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2813.12 | 0.0346651 | 106.03ms | 2889 | 640 | 73.7703 | 979.397 | 0.0466065 | 0.856571 | 1(Win) | true |
| Glaze | 2339.11 | 0.036367 | 126.503ms | 2889 | 320 | 58.7163 | 1177.87 | 0.0503834 | 1.03506 | 2(Loss) | true |
| Jsonifier (two-stage) | 2285.72 | 0.0969182 | 129.216ms | 2889 | 160 | 218.363 | 1205.38 | 0.0968671 | 1.05945 | 3(Loss) | true |
| simdjson (ondemand) | 1088.91 | 0.109931 | 261.944ms | 2889 | 30 | 232.097 | 2530.2 | 0.0685527 | 2.24659 | 4(Loss) | true |
