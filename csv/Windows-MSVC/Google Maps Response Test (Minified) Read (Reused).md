
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1504.98 | 0.102039 | 868.655ms | 11812 | 40 | 2333.33 | 7485 | 0.156111 | 1.63661 | 1(Win) | true |
| Jsonifier (two-stage) | 1227.61 | 0.175195 | 1034.99ms | 11812 | 4890 | 1.26379e+06 | 9176.18 | 0.206841 | 2.01 | 2(Loss) | true |
| Glaze | 980.134 | 0.582708 | 1321.51ms | 11812 | 160 | 717625 | 11493.1 | 1.04929 | 2.51937 | 3(Loss) | true |
| simdjson (ondemand) | 656.84 | 0.679393 | 1850.09ms | 11812 | 80 | 1.08608e+06 | 17150 | 0.131023 | 3.76176 | 4(Loss) | true |
