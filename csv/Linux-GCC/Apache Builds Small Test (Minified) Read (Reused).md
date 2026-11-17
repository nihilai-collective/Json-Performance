
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2856.33 | 0.125683 | 825.803ms | 2632 | 40 | 48.7942 | 878.775 | 0.00474167 | 1.85395 | 7.25342 | 1.07713 | 0.000759878 | 1.8997e-05 | 0 | 1(Win) | true |
| Glaze | 2474.33 | 0.0678986 | 842.477ms | 2632 | 4890 | 2320 | 1014.45 | 0.0148374 | 2.12277 | 9.23367 | 1.68351 | 0.0010082 | 3.26328e-05 | 1.0256e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2366.66 | 0.0920796 | 849.603ms | 2632 | 1280 | 1220.78 | 1060.6 | 0.0744163 | 2.23231 | 9.23252 | 1.3636 | 0.000760769 | 6.73798e-05 | 3.05732e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1956.37 | 0.0532634 | 871.116ms | 2632 | 4890 | 2283.7 | 1283.03 | 0.0452764 | 2.65989 | 8.95061 | 1.58245 | 0.00195105 | 6.30901e-05 | 1.88027e-05 | 4(Loss) | true |
| simdjson (reflection) | 1938.73 | 0.0577793 | 867.675ms | 2632 | 4890 | 2736.48 | 1294.7 | 0.160658 | 2.70314 | 8.7462 | 1.35524 | 0.00173234 | 0.000153452 | 8.08828e-05 | 5(Loss) | true |
