
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2292.11 | 0.0397905 | 3081.74ms | 56369 | 640 | 55737.5 | 23453.3 | 0.050218 | 2.20746 | 9.42132 | 1.80171 | 0.00265541 | 2.19813e-05 | 1.35824e-05 | 1(Win) | true |
| Glaze | 1956.62 | 0.155331 | 3515.52ms | 56369 | 640 | 1.16564e+06 | 27474.8 | 0.426978 | 2.6013 | 11.2196 | 2.27575 | 0.00582848 | 9.00872e-05 | 6.79673e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1847.45 | 0.0586013 | 3658.68ms | 56369 | 320 | 93046.2 | 29098.2 | 0.132628 | 2.73841 | 12.2726 | 2.12839 | 0.00444853 | 1.02006e-05 | 4.93401e-06 | 3(Loss) | true |
| simdjson (reflection) | 1573.57 | 0.0557427 | 4195.99ms | 56369 | 640 | 232095 | 34162.9 | 0.0341445 | 3.21041 | 13.7996 | 2.40327 | 0.00446428 | 6.07881e-05 | 3.10454e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1339.85 | 0.0215338 | 4749.69ms | 56369 | 4890 | 365019 | 40122.1 | 0.00970326 | 3.77103 | 15.0255 | 2.78814 | 0.00854286 | 5.2078e-05 | 3.32022e-05 | 5(Loss) | true |
