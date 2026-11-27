
----
### Github Events Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16066.5 | 0.141651 | 346.547ms | 58581 | 40 | 970.449 | 3477.25 | 0.0772279 | 0.152952 | 1(Win) | true |
| Glaze | 5981.02 | 0.0942286 | 937.807ms | 58581 | 4890 | 378824 | 9340.75 | 0.0103069 | 0.412802 | 2(Loss) | true |
