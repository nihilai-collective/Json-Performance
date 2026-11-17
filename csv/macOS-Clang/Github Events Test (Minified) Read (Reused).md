
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2107.17 | 0.36768 | 2889ms | 53331 | 2560 | 2.01623e+07 | 24136.8 | 0.509707 | 1(Win) | true |
| Glaze | 1852.57 | 0.514581 | 3572.35ms | 53331 | 320 | 6.38662e+06 | 27454 | 2.26547 | 2(Loss) | true |
| Jsonifier (two-stage) | 1772.69 | 0.244439 | 3612.9ms | 53331 | 2560 | 1.25915e+07 | 28691.2 | 0.357317 | 3(Loss) | true |
| simdjson (ondemand) | 890.523 | 0.267054 | 6481.9ms | 53331 | 2560 | 5.95533e+07 | 57113 | 1.0693 | 4(Loss) | true |
