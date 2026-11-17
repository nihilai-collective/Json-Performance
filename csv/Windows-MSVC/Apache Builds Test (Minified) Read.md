
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 822.803 | 1.36985 | 5738.49ms | 94653 | 160 | 3.61366e+08 | 109708 | 0.158055 | 3.00798 | 1(Win) | true |
| Jsonifier (two-stage) | 790.528 | 0.777322 | 5852.87ms | 94653 | 320 | 2.52108e+08 | 114187 | 0.330324 | 3.13081 | 2(Loss) | true |
| Glaze | 761.715 | 0.585004 | 6228.25ms | 94653 | 640 | 3.07596e+08 | 118506 | 0.388626 | 3.24923 | 3(Loss) | true |
| simdjson (ondemand) | 691.813 | 0.273693 | 6807.59ms | 94653 | 2560 | 3.26481e+08 | 130481 | 1.51752 | 3.57779 | 4(Loss) | true |
