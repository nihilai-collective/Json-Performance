
----
### Github Events Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2825.66 | 0.26506 | 794.162ms | 1691 | 2560 | 5858.33 | 570.72 | 0.276249 | 1.94116 | 5.98167 | 1.07274 | 0.00177964 | 0.000142066 | 5.75196e-05 | 1(Win) | true |
| Glaze | 2304.95 | 0.206069 | 816.573ms | 1691 | 4890 | 10164.9 | 699.653 | 0.140252 | 2.33547 | 8.78238 | 1.57836 | 0.000865765 | 0.000124804 | 3.60383e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2121.08 | 0.348035 | 819.574ms | 1691 | 640 | 4481.27 | 760.305 | 0.268085 | 2.51699 | 9.22531 | 1.39858 | 0.000602454 | 7.20727e-05 | 1.84802e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1551.46 | 0.304965 | 849.386ms | 1691 | 40 | 401.946 | 1039.45 | 0.107544 | 3.38733 | 11.1331 | 1.73034 | 0.00144885 | 0.000103489 | 2.95683e-05 | 4(Loss) | true |
