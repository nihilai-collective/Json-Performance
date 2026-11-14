
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2127.41 | 0.100812 | 896.004ms | 3223 | 160 | 339.44 | 1444.81 | 0.0212011 | 2.49005 | 10.0689 | 1.65622 | 0.00108788 | 7.56283e-05 | 3.87837e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 1661.41 | 0.0470102 | 939.359ms | 3223 | 4890 | 3698.8 | 1850.05 | 0.0169353 | 3.12136 | 12.6292 | 2.00528 | 0.00111634 | 0.000115923 | 4.49225e-05 | 2(Loss) | true |
| Glaze | 1574.99 | 0.117209 | 949.946ms | 3223 | 80 | 418.578 | 1951.56 | 0.103229 | 3.28017 | 13.0661 | 2.43376 | 0.00119066 | 5.81756e-05 | 7.75675e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1424.76 | 0.0489741 | 968.257ms | 3223 | 4890 | 5458.6 | 2157.34 | 0.102368 | 3.64159 | 14.1849 | 2.33509 | 0.00183821 | 0.000131849 | 5.39324e-05 | 4(Loss) | true |
| simdjson (reflection) | 1342.24 | 0.333292 | 989.314ms | 3223 | 40 | 2330.08 | 2289.97 | 0.0374682 | 3.83705 | 14.1112 | 2.27087 | 0.00268383 | 7.75675e-05 | 0 | 5(Loss) | true |
