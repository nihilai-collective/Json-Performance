
----
### Google Maps Response Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2499.78 | 0.107058 | 449.548ms | 11812 | 40 | 930.994 | 4506.32 | 0.034593 | 0.984782 | 1(Win) | true |
| Jsonifier (two-stage) | 1867.79 | 0.0663484 | 607.636ms | 11812 | 30 | 480.369 | 6031.1 | 0.060833 | 1.32009 | 2(Loss) | true |
| Glaze | 1733.54 | 0.0708516 | 664.019ms | 11812 | 30 | 635.913 | 6498.13 | 0.205278 | 1.42223 | 3(Loss) | true |
| simdjson (ondemand) | 1013.71 | 0.102681 | 1118.52ms | 11812 | 4890 | 636662 | 11112.4 | 0.246001 | 2.43666 | 4(Loss) | true |
