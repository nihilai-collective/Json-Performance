
----
### Twitter Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2941.51 | 0.120853 | 102.309ms | 2889 | 80 | 102.509 | 936.65 | 0.130957 | 0.816455 | 1(Win) | true |
| Glaze | 2188.38 | 0.121328 | 132.783ms | 2889 | 30 | 70 | 1259 | 0.159109 | 1.10603 | 2(Loss) | true |
| Jsonifier (two-stage) | 2133.4 | 0.0840298 | 147.616ms | 2889 | 160 | 188.424 | 1291.44 | 0.0295125 | 1.13563 | 3(Loss) | true |
| simdjson (reflection) | 2115.03 | 0.0853855 | 141.595ms | 2889 | 160 | 197.948 | 1302.66 | 0.156166 | 1.14606 | 4(Loss) | true |
| simdjson (ondemand) | 1139.42 | 0.0703789 | 241.26ms | 2889 | 160 | 463.375 | 2418.04 | 0.490652 | 2.14813 | 5(Loss) | true |
