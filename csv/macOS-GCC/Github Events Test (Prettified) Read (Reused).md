
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2172.52 | 0.402917 | 3613.99ms | 65103 | 320 | 4.24283e+06 | 28578.4 | 0.00839725 | 1(Win) | true |
| Glaze | 1973.45 | 0.140366 | 3819.8ms | 65103 | 2560 | 4.99246e+06 | 31461.2 | 0.0687032 | 2(Loss) | true |
| Jsonifier (two-stage) | 1954.41 | 0.205293 | 3879.93ms | 65103 | 1280 | 5.44411e+06 | 31767.6 | 0.0541139 | 3(Loss) | true |
| simdjson (reflection) | 1575.87 | 0.0898951 | 4635.35ms | 65103 | 4890 | 6.13397e+06 | 39398.6 | 0.345119 | 4(Loss) | true |
| simdjson (ondemand) | 1346.9 | 0.147592 | 5248.66ms | 65103 | 1280 | 5.92472e+06 | 46096.4 | 0.517235 | 5(Loss) | true |
