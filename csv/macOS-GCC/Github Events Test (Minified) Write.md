
----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12423 | 2.58477 | 465.732ms | 58581 | 30 | 405344 | 4497.07 | 2.3301 | 1(Win) | true |
| simdjson (reflection) | 11120.1 | 0.419083 | 552.567ms | 58581 | 80 | 35464.1 | 5024 | 0 | 2(Loss) | true |
| Glaze | 2920.46 | 0.758151 | 1812.72ms | 58581 | 640 | 1.34618e+07 | 19129.6 | 0.862355 | 3(Loss) | true |
