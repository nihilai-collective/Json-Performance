
----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1433.29 | 0.905079 | 1000.17ms | 11812 | 160 | 809597 | 7859.38 | 2.47402 | 2.11543 | 1(Win) | true |
| Jsonifier (two-stage) | 1233.48 | 0.172633 | 1095.99ms | 11812 | 40 | 9942.31 | 9132.5 | 0.445131 | 2.46084 | 2(Loss) | true |
| Glaze | 1129.02 | 0.467197 | 1204.61ms | 11812 | 40 | 86916.7 | 9977.5 | 0.2428 | 2.68498 | 3(Loss) | true |
| simdjson (ondemand) | 610.595 | 1.25988 | 1928.44ms | 11812 | 4890 | 2.64185e+08 | 18448.9 | 2.42518 | 4.97081 | 4(Loss) | true |
