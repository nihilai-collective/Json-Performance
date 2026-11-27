
----
### Github Events Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16670.3 | 0.393325 | 455.376ms | 78778 | 640 | 201096 | 4506.73 | 0.0102635 | 0.147622 | 1(Win) | true |
| Glaze | 5151.01 | 0.122463 | 1469.45ms | 78778 | 2560 | 816727 | 14585.2 | 0.810401 | 0.479735 | 2(Loss) | true |
| simdjson (reflection) | 679.815 | 0.124253 | 5657.5ms | 78778 | 640 | 1.20677e+07 | 110513 | 0.0209037 | 3.64037 | 3(Loss) | true |
