
----
### Github Events Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14934.1 | 0.115008 | 15.1877ms | 1996 | 1280 | 27.506 | 127.463 | 0.0171649 | 0.132092 | 1(Win) | true |
| Glaze | 4622.03 | 0.0714109 | 43.9514ms | 1996 | 640 | 55.3559 | 411.839 | 0.0557401 | 0.502782 | 2(Loss) | true |
